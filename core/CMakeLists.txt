m4c0_add_interface(
  TARGET m4c0-core
  ALIAS m4c0::core
  )

m4c0_add_test(
  ALIAS m4c0::core::fifo-worker
  TARGET m4c0-test-fifo-worker
  SOURCES tst/test-fifo-worker.cpp
  LIBRARIES m4c0::core m4c0::test)

m4c0_add_test(
  ALIAS m4c0::core::function
  TARGET m4c0-test-function
  SOURCES tst/test-function.cpp
  LIBRARIES m4c0::core m4c0::test)

m4c0_add_test(
  ALIAS m4c0::core::pimpl
  TARGET m4c0-test-pimpl
  SOURCES tst/test-pimpl.cpp
  LIBRARIES m4c0::core m4c0::test)
