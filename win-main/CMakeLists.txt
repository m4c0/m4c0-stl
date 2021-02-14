m4c0_add_library(
  TARGET m4c0_win_main
  ALIAS m4c0::win::main
  SOURCES src/main.cpp
  )

m4c0_add_test_subdirectory(tst)
