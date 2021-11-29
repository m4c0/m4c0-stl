m4c0_add_interface(
  TARGET m4c0-core
  ALIAS m4c0::core
  )

m4c0_add_test(
  ALIAS m4c0::core::callback-chain
  TARGET m4c0-test-callback-chain
  SOURCES tst/test-callback-chain.cpp
  LIBRARIES m4c0::core m4c0::test)

m4c0_add_test(
  ALIAS m4c0::core::ce-list
  TARGET m4c0-test-ce-list
  SOURCES tst/test-ce-list.cpp
  LIBRARIES m4c0::core)

m4c0_add_test(
  ALIAS m4c0::core::ce-map
  TARGET m4c0-test-ce-map
  SOURCES tst/test-ce-map.cpp
  LIBRARIES m4c0::core)

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
