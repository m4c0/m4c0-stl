m4c0_add_library(
  TARGET m4c0_droid_main
  ALIAS m4c0::droid::main
  SOURCES
    src/glue/android_native_app_glue.c
    src/main.cpp
  LIBRARIES android log
  )

m4c0_add_test(
  TARGET m4c0-test-droid-main-link
  SOURCES tst/test-link.cpp
  LIBRARIES m4c0::droid::main
  )
