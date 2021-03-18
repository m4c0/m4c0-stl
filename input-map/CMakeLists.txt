m4c0_add_interface(
  TARGET m4c0-input-map
  ALIAS m4c0::input_map
  LIBRARIES m4c0::core
  )

m4c0_add_test(
  TARGET m4c0-test-inputmap-link
  SOURCES tst/dummy.cpp
  LIBRARIES m4c0::input_map)
