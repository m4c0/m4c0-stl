m4c0_add_interface(
  TARGET m4c0-png
  LIBRARIES m4c0-io
  )

m4c0_add_test(
  TARGET m4c0-test-png-poc
  ALIAS m4c0::png::poc
  SOURCES tst/poc.cpp
  LIBRARIES m4c0-png
  )
