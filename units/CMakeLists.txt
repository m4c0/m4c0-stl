m4c0_add_interface(
  TARGET m4c0-units
  ALIAS m4c0::units
  )

m4c0_add_test(
  TARGET m4c0-test-units-poc
  SOURCES tst/poc.cpp
  LIBRARIES m4c0::units
  )
