#ifndef __HOOK_UTILS_H
#define __HOOK_UTILS_H
#include "includes.h"

struct Hook {
    uintptr_t address;
    // maybe change to std::function
    void* hook;
    void* detour;
};

namespace Hooks {
    std::vector<Hook> hooks;
    void init();
    void addHook(Hook hook);
    void unload();
}

#endif