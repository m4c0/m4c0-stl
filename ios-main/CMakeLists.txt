m4c0_add_library(
  TARGET m4c0-ios-main
  ALIAS m4c0::ios::main
  SOURCES
    src/M4C0AppDelegate.m
    src/main.cpp
  LIBRARIES
    m4c0::objc::bridge
    "-framework Metal"
    "-framework MetalKit"
    "-framework UIKit"
  )
target_compile_options(m4c0-ios-main PRIVATE -fmodules -fobjc-arc)
target_link_options(m4c0-ios-main PUBLIC -ObjC)
