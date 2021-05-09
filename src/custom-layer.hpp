/*
  You'll see these a lot, they're called include guards, they
  basically make sure your code won't be included multiple times,
  causing weird compile errors
  
  You can also just use:
  #pragma once
  However, cos8o will be really sad if you do :c
  (the actual reason for this is that its not supported on
  some compilers, i think, but it works fine on MSVC)
*/
#ifndef __CUSTOM_LAYER_HPP
#define __CUSTOM_LAYER_HPP

#include "includes.h"

// declare our own class based on CCLayer
class CustomLayer : public CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();
    void backButtonCallback(CCObject*);
public:
    static CustomLayer* create();

    // button callback function. if we were robtop this would be in MenuLayer, however we are not
    void switchToCustomLayerButton(CCObject*);
};

// continue reading on `custom-layer.cpp`

#endif