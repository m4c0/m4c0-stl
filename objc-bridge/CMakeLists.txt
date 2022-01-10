m4c0_add_library(
  TARGET m4c0-objc-bridge
  SOURCES
    src/autorelease.cpp
    src/class_builder.cpp
    src/inject.cpp
    src/middleware.cpp
  LIBRARIES
    m4c0-core
    "-framework Foundation")

m4c0_add_test(
  ALIAS m4c0::objc::bridge::autorelease
  TARGET m4c0-test-objc-bridge-autorelease
  SOURCES tst/test-autorelease.cpp
  LIBRARIES m4c0-objc-bridge m4c0-test)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::class-builder
  TARGET m4c0-test-objc-bridge-class-builder
  SOURCES tst/test-class-builder.cpp
  LIBRARIES m4c0-objc-bridge m4c0-test)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::middleware
  TARGET m4c0-test-objc-bridge-middleware
  SOURCES tst/test-middleware.cpp tst/test-middleware-protos.m
  LIBRARIES m4c0-objc-bridge m4c0-test)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::msg-send
  TARGET m4c0-test-objc-bridge-msg-send
  SOURCES tst/test-msg-send.cpp
  LIBRARIES m4c0-objc-bridge m4c0-test)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::poc
  TARGET m4c0-test-objc-bridge-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0-objc-bridge)

m4c0_add_test(
  ALIAS m4c0::objc::bridge::swizzling
  TARGET m4c0-test-objc-bridge-swizzling
  SOURCES tst/test-swizzling.cpp
  LIBRARIES m4c0-objc-bridge m4c0-test)

