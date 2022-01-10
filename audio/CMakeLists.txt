m4c0_add_library(
  TARGET m4c0-audio
  SOURCES
    $<$<PLATFORM_ID:Android>:src/droid.cpp>
    $<$<PLATFORM_ID:Darwin,iOS>:src/osx.cpp>
    $<$<PLATFORM_ID:Windows>:src/win.cpp>
  LIBRARIES
    m4c0-log
    $<$<PLATFORM_ID:Android>:aaudio>
    $<$<PLATFORM_ID:Darwin,iOS>:-framework\ AudioToolbox>
  )

m4c0_add_test(
  TARGET m4c0-test-audio-link
  LIBRARIES m4c0-audio
  SOURCES tst/test-link.cpp
  )
