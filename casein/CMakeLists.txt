m4c0_add_interface(
  TARGET m4c0-casein
  ALIAS m4c0::casein
  LIBRARIES
    m4c0::native-handles
    $<$<PLATFORM_ID:Android>:m4c0::droid::main>
    $<$<PLATFORM_ID:Darwin>:m4c0::osx::main>
    $<$<PLATFORM_ID:iOS>:m4c0::ios::main>
    $<$<PLATFORM_ID:Windows>:m4c0::win::main>
  )
# Allows replacement of the main class, for extra extensibility
m4c0_add_library(
  TARGET m4c0-casein-main
  ALIAS m4c0::casein::main
  SOURCES
    $<$<PLATFORM_ID:Android>:src/main.droid.cpp>
    $<$<PLATFORM_ID:Darwin>:src/main.osx.cpp>
    $<$<PLATFORM_ID:iOS>:src/main.ios.cpp>
    $<$<PLATFORM_ID:Windows>:src/main.win.cpp>
  LIBRARIES
    m4c0::casein
  )

m4c0_add_test(
  TARGET m4c0-test-casein-link
  SOURCES tst/dummy.cpp
  LIBRARIES m4c0::casein::main)
