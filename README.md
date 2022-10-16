# gd-mod-example
Basic Geometry Dash mod example meant for beginners, or as a template for people who want to use CMake + MinHook + gd.h + cocos2d.
<p align="center">
<img src="https://user-images.githubusercontent.com/26722564/117589440-d7498200-b0ff-11eb-8662-e3f0854a5420.png" alt="screenshot" width="48%">
<img src="https://user-images.githubusercontent.com/26722564/117589450-f1836000-b0ff-11eb-8a94-2e7ce4df48c2.png" alt="screenshot" width="48%">
</p>

For a simpler and easier to setup/use template check out [gd-mod-cpm-template](https://github.com/matcool/gd-mod-cpm-template)

## Usage

Clone the repo and make sure to use the `--recursive` option. If you dont have git you can download a zip of the repo in releases.

Make sure to change the project name on the `CMakeLists.txt` file
```cmake
set(PROJECT_NAME template-project) # change this
```

To build this project you'll need CMake, which you can download [here](https://cmake.org/download/), and a C++ compiler, such as MSVC, which you can get with Visual Studio

**Make sure you're building in 32 bit mode**, as gd (atleast the windows version) is 32 bit, meaning your dll has to be too.

All the source files contain a lot of comments which you should definitely read if you're just starting out :) (i recommend starting from [dllmain.cpp](https://github.com/matcool/gd-mod-example/blob/master/src/dllmain.cpp))

### Manual setup

You can compile this project entirely in the terminal, as long as you have CMake and MSVC already

1. Clone
```bash
git clone --recursive https://github.com/matcool/gd-mod-example my-awesome-mod
cd my-awesome-mod
```
2. Configure (you only need to do this when editing the cmake file, or adding new cpp files)
``` bash
cmake -B build -A win32
```
3. Build
```bash
# config can also be RelWithDebInfo or MinSizeRel
# however avoid using Debug as that breaks gd.h ;)
cmake --build build --config Release
```

## Resources
- [Ghidra](https://ghidra-sre.org/) - A free reverse engineering tool, which is almost mandatory for GD modding
- [GD Programming](https://discord.gg/jEwtDBK) - A discord server where you can ask a lot of questions :D
- [function address dump](https://github.com/matcool/re-scripts/blob/main/func_dump.txt) - A big list of function addresses for windows
- [gd-addresses](https://github.com/spookybear0/gd-addresses/) - A list of publicly known function offsets
- [Cheat Engine](https://cheatengine.org/) - An awesome tool that lets you find values in memory, explore memory in a hex view and debug functions.
- [x32dbg](https://x64dbg.com/) - An advanced debugger
