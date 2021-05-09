#include "custom-layer.hpp"

// This is the create method, a static method that creates
// a new instance, and initializes it.
CustomLayer* CustomLayer::create() {
    auto ret = new CustomLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        // if `new` or `init` went wrong, delete the object and return a nullptr
        delete ret;
        ret = nullptr;
    }
    return ret;
}

// This is the init function, where most of your initialization
// code should be. Here we add nodes to the layer, set their position, etc
bool CustomLayer::init() {
    // This is a bitmap font label, the first argument is the text we want
    // and the second is the .fnt file we want to use. This acts the same as sprites,
    // where we dont need to provide the -hd or -uhd suffix
    auto label = CCLabelBMFont::create("Hello world!", "bigFont.fnt");

    label->setPosition({200, 100});
    label->setRotation(45);

    // equivalent to `this->addChild(label)`
    addChild(label);

    // This enables the "keypad" for the layer, the keypad being
    // the thing with the back button, which in our case is the ESC key
    // later you will see keyBackClicked, which is the function that is called
    setKeypadEnabled(true);

    return true;
}

// this function is called whenever you press ESC on a function (or on mobile, the back button)
void CustomLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
}

// this is the callback function for the button we added in MenuLayer
// inside this function, the `this` pointer will be what we set the 
// target to, so it'll be the instance of MenuLayer
// The only argument to this function `CCObject*` is the button which
// the callback came from. Here its a CCObject as pretty much every
// cocos class inherits CCObject, and can be casted into a pointer of it
void CustomLayer::switchToCustomLayerButton(CCObject* object) {
    /*
      Here we create an instance of our layer, and since its its own
      thing we have to make a scene for it, which can easily be done
      by just using `CCScene::create()`
    */
    auto layer = CustomLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    // Here we create a transition for the layer, which is that black fade
    // present in gd
    auto transition = CCTransitionFade::create(0.5f, scene);
    // use the director to push the transition, which is
    // technically a scene
    CCDirector::sharedDirector()->pushScene(transition);
}