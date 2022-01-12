m4c0_add_interface(
  TARGET m4c0-core
  )

function(m4c0_core_test NAME)
  m4c0_add_test(
    ALIAS m4c0::core::${NAME}
    TARGET m4c0-test-${NAME}
    SOURCES tst/test-${NAME}.cpp
    LIBRARIES m4c0-core m4c0-test)
endfunction()
m4c0_core_test(callback-chain)
m4c0_core_test(fifo-worker)
m4c0_core_test(function)
m4c0_core_test(pimpl)

m4c0_add_test(
  TARGET m4c0-test-constexpr
  SOURCES
    tst/test-ce-list.cpp
    tst/test-ce-map.cpp
    tst/test-crc32.cpp
  LIBRARIES m4c0-core)

