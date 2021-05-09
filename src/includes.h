#ifndef __INCLUDES_H
#define __INCLUDES_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// shut up cocos
#pragma warning(push, 0)
#include <cocos2d.h>
#pragma warning(pop)
#include <MinHook.h>
#include <gd.h>

using std::uintptr_t;

// since everything in cocos2d starts with CC, there is no chance
// for any collision, so it's safe to do this (it also makes using cocos a lot nicer imo)
using namespace cocos2d;

#endif