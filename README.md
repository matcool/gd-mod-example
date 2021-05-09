# gd-mod-example
Basic Geometry Dash mod example meant for beginners, or as a template for people who want to use CMake + MinHook + gd.h + cocos2d.

## Usage

Clone the repo and make sure to use the `--recursive` option. If you dont have git you can download a zip of the repo in releases.

Make sure to change the project name on the `CMakeLists.txt` file
```cmake
set(PROJECT_NAME template-project) # change this
```

To build this project you'll need CMake, which you can download [here](https://cmake.org/download/), and a C++ compiler, such as MSVC, which you can get with Visual Studio

All the source files contain a lot of comments which you should definitely read if you're just starting out :) (i recommend starting from [dllmain.cpp](https://github.com/matcool/gd-mod-example/blob/master/src/dllmain.cpp))

## Resources
- [Ghidra](https://ghidra-sre.org/) - A free reverse engineering tool, which is almost mandatory for GD modding
- [GD Programming](https://discord.gg/jEwtDBK) - A discord server where you can ask a lot of questions :D
- [gd-addresses](https://github.com/spookybear0/gd-addresses/) - A list of publicly known function offsets
- [Cheat Engine](https://cheatengine.org/) - An awesome tool that lets you find values in memory, explore memory in a hex view and debug functions.
- [x32dbg](https://x64dbg.com/) - An advanced debugger