m4c0_add_interface(
  ALIAS m4c0::objc::bridge
  TARGET m4c0-objc-bridge
  LIBRARIES "-framework Foundation")

m4c0_add_test(
  ALIAS m4c0::objc::bridge::poc
  TARGET m4c0-objc-bridge-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0::objc::bridge m4c0::test)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::autorelease
  TARGET m4c0-objc-bridge-autorelease
  SOURCES tst/test-autorelease.cpp
  LIBRARIES m4c0::objc::bridge m4c0::test)
