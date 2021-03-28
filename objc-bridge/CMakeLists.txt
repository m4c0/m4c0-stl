m4c0_add_test(
  ALIAS m4c0::objc_bridge::poc
  TARGET m4c0-objc-bridge-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0::test "-framework Foundation")
