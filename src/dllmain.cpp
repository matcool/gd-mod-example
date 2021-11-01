#include "includes.h"
#include "custom-layer.hpp"

/*
  Here we define the hook function and the trampoline function, with
  the first being a global variable with a function type, and the other
  is an actual function. The actual calling convention for this function
  is __thiscall, since its a class method, however, c++ doesn't let you
  use __thiscall outside classes and function types, so we have to approximate
  it using __fastcall, which can be done by having `this` be the first
  argument and between actual arguments, an unused arg which is the `edx`
  register. so for example
  
    PlayLayer::init(GJGameLevel*)
  
  would be
  
    PlayLayer_init_H(PlayLayer*, void*, GJGameLevel*)
  
  If the function doesn't have any arguments (which is the case here),
  the `void*` for the edx register is not needed, however i still left it in
  here for the explanation
  
  PS: not every function is a __thiscall, for example, if they're static
  they can be __fastcall, which is much easier to deal with, or sometimes,
  they get really optimized and floats go into xmm registers, and in that
  case you have to do some asm to call/hook the function properly :(
  
  PS2: this calling convention shenanigans only happens on x86, on 64 bit
  (the only 64 bit version of gd being the mac version), you don't have to
  worry about this
*/
bool (__thiscall* MenuLayer_init)(CCLayer* self);
bool __fastcall MenuLayer_init_H(CCLayer* self, void*) {
    /*
      In cocos2d-x, init functions return a boolean, which is false if
      the initialization went wrong, so here we check for it. most of the time
      gd just crashes if an init function goes wrong so this is kinda useless,
      except for the part where we return true at the end
    */
    if (!MenuLayer_init(self)) return false;

    /*
      Note that we're using the one without the -uhd and -hd suffix; which is
      because gd deals with selecting the right resolution texture for us.
      Note that this texture is also its own file in the gd Resources/ folder,
      meaning you access it via CCSprite::create
    */
    auto sprite = CCSprite::create("dialogIcon_017.png");

    /*
      Also note that this one is different, as the texture is contained within a
      spritesheet, so for that we use CCSprite::createWithSpriteFrameName
      For finding the name of a texture that is inside a spritesheet, you can either
      look at the .plist file directly, or use Absolute's texture splitter.
    */
    auto buttonSprite = CCSprite::createWithSpriteFrameName("GJ_stopEditorBtn_001.png");

    /*
      As with every CCNode, you can set it's position, scale, rotation, etc.
      cocos2d-x's position system is based off the bottom left corner of your screen,
      and the values aren't in pixels (sometimes they aren't even consistent), so
      positioning may require a lot of trial and error.
    */
    sprite->setPosition({100, 100});
    sprite->setScale(0.5f);
    // make sure to actually add it to the layer, otherwise nothing will show up
    self->addChild(sprite);

    /*
      Here we create a button using one of rob's classes, CCMenuItemSpriteExtra
      (despite the name it's not in cocos2d), and to do this we use gd.h, which
      contains a bunch of useful functions.
      CCMenuItemSpriteExtra is the button you can click on and it does a bounce animation
    */
    auto button = gd::CCMenuItemSpriteExtra::create(
        buttonSprite, // the sprite the button will use
        /*
          Here is the "target" for the callback function, most of the time it
          will be the current `this` (in our case self) and since callback
          functions have to be class methods, the target will be
          the `this` pointer in the method. It can be anything (except 0) but
          it's an useful way of using something in the callback.
        */
        self,
        /*
          Here is the callback that is called when you press the button. It's
          wrapped in a macro, which casts it to the correct type used by cocos.
          The callback is in CustomLayer because as previously mentioned, it has to
          be a class method, and we're not inside a class. I could just create a class
          specifically for this callback (say `Callback::switchToCustomLayer`), but i
          find that kinda messy and we can just use this class anyways.
        */
        menu_selector(CustomLayer::switchToCustomLayerButton)
    );

    // continue reading on `custom-layer.hpp`, where our CustomLayer is defined

    // All CCMenuItems need to be in a CCMenu to work,
    // otherwise you can't click on the button
    auto menu = CCMenu::create();
    menu->addChild(button);
    menu->setPosition({150, 100});

    self->addChild(menu);

    return true;
}

DWORD WINAPI thread_func(void* hModule) {
    // initialize minhook
    MH_Initialize();

    /*
      `uintptr_t` is a type which is always the size of a pointer, in this case it is
      32 bit / 4 bytes. The usage of it here is kinda reduntant since this code is not
      cross-platform, however i think it looks neat and it makes it easy to tell if
      something is an address.
    */
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    
    /*
      Here we are hooking MenuLayer::init, by giving the starting address of the function
      and what function to hook it to, as well as a trampoline, which is used to call the
      original function without going through our hook.

      Hooking is quite a complex process and can be confusing to beginners, so if you
      want a more detailed explanation you can watch this video by Guided Hacking
      https://www.youtube.com/watch?v=jTl3MFVKSUM (in the video he makes his own
      hook method, however here we just use MinHook as its a lot simpler to use
      and does the dissassembly part for us).
      To give a basic explanation: hooking a function means overwriting its first few
      instructions, making it redirect code execution to our own function.

      Hooking the init function of a node (in this case a layer) is a common practice as
      that is where you should initialize the elements in the node, and in a hook, you
      can add your own nodes.
    */
    MH_CreateHook(
        reinterpret_cast<void*>(base + 0x1907b0),
        reinterpret_cast<void*>(&MenuLayer_init_H),
        reinterpret_cast<void**>(&MenuLayer_init) // note the &, this gets the address of the variable
    );

    // enable all hooks you've created with minhook
    MH_EnableHook(MH_ALL_HOOKS);

    return 0;
}

/*
This function runs whenever we inject our dll, this is present
in pretty much every mod, and is just winapi boilerplate
*/
BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        auto h = CreateThread(0, 0, thread_func, handle, 0, 0);
        if (h)
            CloseHandle(h);
        else
            return FALSE;
    }
    return TRUE;
}