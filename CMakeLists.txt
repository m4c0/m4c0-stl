# 3.20.4 solves an issue with MSVC and /std:c++latest
# See: https://stackoverflow.com/a/64890021
cmake_minimum_required(VERSION 3.20.4)
project(m4c0-stl
  VERSION 1.0.0
  DESCRIPTION "m4c0's C++ Standard Library"
  LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/library-utils.cmake)
include(cmake/test-utils.cmake)

add_subdirectory(assets)
add_subdirectory(audio)
add_subdirectory(casein)
add_subdirectory(containers)
add_subdirectory(core)
add_subdirectory(di)
add_subdirectory(ext)
add_subdirectory(fuji)
add_subdirectory(io)
add_subdirectory(log)
add_subdirectory(maze)
add_subdirectory(native-handles)
add_subdirectory(parser)
add_subdirectory(png)
add_subdirectory(riff)
add_subdirectory(test)
add_subdirectory(units)
add_subdirectory(vulkan)
add_subdirectory(vulkan-actions)
add_subdirectory(vulkan-commands)
add_subdirectory(vulkan-dynamic)
add_subdirectory(vulkan-objects)
add_subdirectory(vulkan-static)
add_subdirectory(vulkan-tools)

if(APPLE)
  enable_language(OBJC OBJCXX)
  add_subdirectory(objc-bridge)
  add_subdirectory(objc-wraps)
endif()

if(ANDROID)
  add_subdirectory(droid-main)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_subdirectory(osx-main)
elseif(CMAKE_SYSTEM_NAME STREQUAL "iOS")
  add_subdirectory(ios-main)
elseif(WIN32)
  add_subdirectory(win-main)
endif()

