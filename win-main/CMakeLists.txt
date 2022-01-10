m4c0_add_library(
  TARGET m4c0_win_main
  SOURCES src/main.cpp
  )

m4c0_add_test(
  TARGET m4c0-test-win-main-link 
  SOURCES tst/dummy.cpp
  LIBRARIES m4c0-win-main
  WIN32)
