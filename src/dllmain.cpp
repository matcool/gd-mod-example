#include "includes.h"
#include "hook_utils.hpp"
#include "utils.hpp"

inline int(__thiscall* MenuLayer_init)(CCLayer* self);
int __fastcall MenuLayer_initHook(CCLayer* self, void*) {
    auto ret = MenuLayer_init(self);

    auto label = CCLabelBMFont::create("Hello World", "bigFont.fnt");
    label->setPosition({ 200, 100 });
    label->setScale(0.5f);

    self->addChild(label);

    return ret;
}

DWORD WINAPI myThread(void* hModule) {
    Hooks::init();
    auto base = cast<uintptr_t>(GetModuleHandle(0));
    Hooks::addHook({ base + 0x1907b0, MenuLayer_initHook, &MenuLayer_init });

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0x1000, myThread, hModule, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            Hooks::unload();
            break;
    }
    return TRUE;
}