#include "hook_utils.hpp"

void Hooks::init() {
    MH_Initialize();
}

void Hooks::addHook(Hook hook) {
    auto target = reinterpret_cast<void*>(hook.address);
    MH_CreateHook(target, hook.hook, reinterpret_cast<void**>(hook.detour));
    MH_EnableHook(target);
    hooks.push_back(hook);
}

void Hooks::unload() {
    MH_Uninitialize();
}