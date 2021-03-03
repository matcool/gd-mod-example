#include "includes.h"
// #include "hook_utils.hpp"

inline int(__thiscall* pl_init)(CCLayer* self);
int __fastcall pl_initHook(CCLayer* self, void*) {
    auto ret = pl_init(self);

    auto label = CCLabelBMFont::create("Hello from cmake generated dll", "bigFont.fnt");
    label->setPosition({ 100, 100 });
    self->addChild(label);

    return ret;
}

DWORD WINAPI myThread(void* hModule) {
    //Hooks::init();
    MH_Initialize();
    auto base = reinterpret_cast<uintptr_t>(GetModuleHandle(0));
    //Hooks::addHook({ base + 0x1907b0, pl_initHook, pl_init });
    MH_CreateHook((void*)(base + 0x1907b0), pl_initHook, (void**)(&pl_init));

    MH_EnableHook(MH_ALL_HOOKS);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0x1000, myThread, hModule, 0, 0);
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}