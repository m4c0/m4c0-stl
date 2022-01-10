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

function(m4c0_core_ce_test NAME)
  m4c0_add_test(
    TARGET m4c0-test-ce-${NAME}
    SOURCES tst/test-ce-${NAME}.cpp
    LIBRARIES m4c0-core)
endfunction()
m4c0_core_ce_test(list)
m4c0_core_ce_test(map)

