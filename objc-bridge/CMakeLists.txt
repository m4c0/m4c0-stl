m4c0_add_library(
  ALIAS m4c0::objc::bridge
  TARGET m4c0-objc-bridge
  SOURCES
    src/autorelease.cpp
    src/class_builder.cpp
    src/inject.cpp
    src/middleware.cpp
  LIBRARIES
    m4c0::core
    "-framework Foundation")

m4c0_add_test(
  ALIAS m4c0::objc::bridge::autorelease
  TARGET m4c0-test-objc-bridge-autorelease
  SOURCES tst/test-autorelease.cpp
  LIBRARIES m4c0::objc::bridge m4c0::test)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::middleware
  TARGET m4c0-test-objc-bridge-middleware
  SOURCES tst/test-middleware.cpp tst/test-middleware-protos.m
  LIBRARIES m4c0::objc::bridge m4c0::test)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::poc
  TARGET m4c0-test-objc-bridge-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0::objc::bridge)

