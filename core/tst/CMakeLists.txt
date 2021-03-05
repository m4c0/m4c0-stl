m4c0_add_test(
  ALIAS m4c0::core::function
  TARGET m4c0-test-function
  SOURCES test-function.cpp
  LIBRARIES m4c0::core m4c0::test)

m4c0_add_test(
  ALIAS m4c0::core::pimpl
  TARGET m4c0-test-pimpl
  SOURCES test-pimpl.cpp
  LIBRARIES m4c0::core m4c0::test)
