cmake_minimum_required(VERSION 3.17..3.19)
project(m4c0-stl
  VERSION 1.0.0
  DESCRIPTION "m4c0's C++ Standard Library"
  LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/library-utils.cmake)
include(cmake/test-utils.cmake)

add_subdirectory(assets)
add_subdirectory(casein)
add_subdirectory(core)
add_subdirectory(di)
add_subdirectory(ext)
add_subdirectory(fuji)
add_subdirectory(log)
add_subdirectory(maze)
add_subdirectory(native-handles)
add_subdirectory(test)
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

