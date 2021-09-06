m4c0_add_interface(
  TARGET m4c0-parser
  ALIAS m4c0::parser
  )

m4c0_add_test(
  TARGET m4c0-test-parser-constexpr
  SOURCES tst/result.cpp
  LIBRARIES m4c0::parser
  )

m4c0_add_test(
  TARGET m4c0-test-parser-polish
  ALIAS m4c0::parser::polish
  SOURCES tst/polish.cpp
  LIBRARIES m4c0::parser m4c0::test
  )
