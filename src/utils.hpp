#ifndef __UTILS_HPP
#define __UTILS_HPP
#include "includes.h"

template <typename T, typename R>
T cast(const R v) { return reinterpret_cast<T>(v); }

std::uintptr_t follow(std::uintptr_t addr) { return *cast<std::uintptr_t*>(addr); }
void* follow(void* addr) { return *cast<void**>(addr); }

template <typename T, typename U, typename V>
auto createHook(T addr, U hook, V* original) {
    return MH_CreateHook(cast<void*>(addr), cast<void*>(hook), cast<void**>(original));
}

#endif