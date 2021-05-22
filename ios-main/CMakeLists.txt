m4c0_add_library(
  TARGET m4c0-ios-main
  ALIAS m4c0::ios::main
  SOURCES
    src/main.cpp
  LIBRARIES
    m4c0::objc::bridge
    m4c0::objc::wraps
    "-framework Metal"
    "-framework MetalKit"
    "-framework UIKit"
  )
target_compile_options(m4c0-ios-main PRIVATE -fmodules -fobjc-arc)
target_link_options(m4c0-ios-main PUBLIC -ObjC)
