m4c0_add_library(
  TARGET m4c0_ios_main
  ALIAS m4c0::ios::main
  SOURCES
    src/app_delegate.cpp
    src/main.cpp
    src/main.m
  LIBRARIES
    m4c0::objc::bridge
    "-framework Metal"
    "-framework MetalKit"
    "-framework UIKit"
  )
