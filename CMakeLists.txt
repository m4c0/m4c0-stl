cmake_minimum_required(VERSION 3.17..3.19)
project(m4c0-stl
  VERSION 1.0.0
  DESCRIPTION "m4c0's C++ Standard Library"
  LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/library-utils.cmake)
include(cmake/test-utils.cmake)

add_subdirectory(core)
add_subdirectory(di)
add_subdirectory(ext)
add_subdirectory(log)
add_subdirectory(maze)
add_subdirectory(test)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  enable_language(OBJC OBJCXX)
  add_subdirectory(objc-bridge)
  add_subdirectory(osx-main)
elseif(WIN32)
  add_subdirectory(win-main)
endif()

