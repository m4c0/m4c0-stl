m4c0_add_library(
  TARGET m4c0_osx_main
  ALIAS m4c0::osx::main
  OBJCXX
  SOURCES
    src/M4C0AppDelegate.mm
    src/M4C0Window.mm
    src/main.mm
  LIBRARIES
    "-framework Cocoa"
  )

m4c0_add_test_subdirectory(tst)
