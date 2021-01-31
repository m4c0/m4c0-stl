cmake_minimum_required(VERSION 3.17..3.19)
project(m4c0-stl
  VERSION 1.0.0
  DESCRIPTION "m4c0's C++ Standard Library"
  LANGUAGES C CXX)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(core)
add_subdirectory(di)
add_subdirectory(ext)
add_subdirectory(test)

