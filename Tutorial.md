# Tutorial

This assumes you have at least some knowledge of C++. You should not jump into GD Modding with little c++ or programming knowledge. that is dumb bad idea

- [How do mods work](#how-do-mods-work)
    - [Mods in the future](#mods-in-the-future)
- [Setup](#setup)
- [Your first dll]()
- [Setting up libraries]()
- [Your first Cocos2d-x layer]()
- [Working with the gd classes]()
- [Understanding assembly]()
- [Reverse engineering]()
    - [Depression]()

# How do mods work

Geometry Dash is a game written in C++ using the Cocos2d-x framework. Like many c++ applications, it's natively compiled, meaning you can't just edit some nice and neat source code thats available, instead all you have is assembly, which is what your cpu runs.

So how can you mod the game if there's no official tools or public source code? The answer is pain. lots of it. Just kidding! it is done with methods such as injection, patching and hooking. So first, **what is injection**?

> DLL injection is a technique used for running code within the address space of another process by forcing it to load a dynamic-link library. DLL injection is often used by external programs to influence the behavior of another program in a way its authors did not anticipate or intend. \
[*From: https://en.wikipedia.org/wiki/DLL_injection*](https://en.wikipedia.org/wiki/DLL_injection)

Well, basically it's *injecting* our own code into another process via dynamic libraries, such as .dll files on Windows. This is sort of what mods do, except there is no other process involved, it's all done in gd.

**What is patching**? Patching, or in this context, binary patching is modifying existing bytes. It can be either done in memory, meaning its temporary, or it can be done by directly editing the game's executable, thus making the change persistent

**What is hooking**? 

> The term hooking covers a range of techniques used to alter the behaviour of software by **intercepting** function calls or messages or events passed between software components. Code that handles such intercepted function calls, events or messages is called a hook. \
Runtime function hooking can be implemented by changing the very first few code instructions of the target function to jump to an injected code. \
[*From: https://en.wikipedia.org/wiki/Hooking*](https://en.wikipedia.org/wiki/Hooking)

In short, it's basically redirecting a target function, so that whenever it gets executed it'll run our own code, which is called the hook. On native code this works by overwriting the assembly code at the start of the target function. In GD modding this is essentially what allows 90% of the stuff to happen, since it lets you add on to what's already in the game.

Mods are usually distributed as dynamic libraries (with file extensions such as `.dll` on Windows, `.dylib` on MacOS and `.so` on Android), and loaded through [mod loaders](). Mod loaders and DLL Injectors are quite similar, they can load arbitrary libraries, although injectors work externally to the process, while mod loaders are in the target process.

## Mods in the future

This repo shows the process of making a mod for windows which involves gd.h + cocos-headers + minhook, however tools and sdks such as [lilac](https://github.com/lilac-sdk), [hyperdash]() and [Cacao](https://github.com/camila314/CacaoSDK) intend to provide a much better experience in modding, and reducing conflicts between mods. At the moment of writing this, there is no usable SDK for windows

# Setup

First u need to install clang or visual studio. choose wisely. it will determinate your destiny.