cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_NAME template-project)
project(${PROJECT_NAME})

find_file(WINDOWS_HEADER windows.h)
if(NOT WINDOWS_HEADER)
  message(FATAL_ERROR "Can't find windows.h!")
endif()

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  libraries/minhook/include
  libraries/gd.h/include
  libraries/gd.h/
  libraries/cocos-headers/cocos2dx/
  libraries/cocos-headers/cocos2dx/include
  libraries/cocos-headers/cocos2dx/kazmath/include
  libraries/cocos-headers/cocos2dx/platform/win32
  libraries/cocos-headers/cocos2dx/platform/third_party/win32
  libraries/cocos-headers/cocos2dx/platform/third_party/win32/OGLES
)

add_subdirectory(libraries/minhook)
target_link_libraries(${PROJECT_NAME} minhook)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libraries/cocos-headers/cocos2dx/libcocos2d.lib)
# not needed most of the time
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libraries/cocos-headers/extensions/libExtensions.lib)