m4c0_add_library(
  TARGET m4c0_osx_main
  ALIAS m4c0::osx::main
  OBJCXX
  SOURCES
    src/M4C0AppDelegate.mm
    src/M4C0Window.mm
    src/main.mm
  LIBRARIES
    m4c0::objc::bridge
    "-framework Cocoa"
    "-framework MetalKit"
  )

m4c0_add_test(
  TARGET m4c0-test-osx-main-link
  SOURCES tst/dummy.cpp
  LIBRARIES m4c0::osx::main)
