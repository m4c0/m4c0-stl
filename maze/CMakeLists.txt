m4c0_add_interface(
  TARGET m4c0-maze
  ALIAS m4c0::maze
  )

m4c0_add_test(
  ALIAS m4c0::maze
  TARGET m4c0-test-maze
  SOURCES tst/dummy.cpp
  LIBRARIES m4c0::maze m4c0::test)
