m4c0_add_library(
  TARGET m4c0-droid-main
  SOURCES
    src/glue/android_native_app_glue.c
    src/main.cpp
  LIBRARIES android log
  )
target_link_options(m4c0-droid-main PUBLIC "-u ANativeActivity_onCreate")

m4c0_add_test(
  TARGET m4c0-test-droid-main-link
  SOURCES tst/test-link.cpp
  LIBRARIES m4c0-droid-main
  )
