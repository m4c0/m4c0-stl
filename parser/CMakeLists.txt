m4c0_add_interface(
  TARGET m4c0-parser
  ALIAS m4c0::parser
  )

m4c0_add_test(
  TARGET m4c0-test-parser-constexpr
  SOURCES 
    tst/brainf.cpp
    tst/combiners.cpp
    tst/concept.cpp
    tst/constants.cpp
    tst/conversions.cpp
    tst/exoterics.cpp
    tst/numeric.cpp
    tst/polish.cpp
    tst/result.cpp
    tst/str.cpp
    tst/string_view.cpp
    tst/tokeniser.cpp
    tst/traits.cpp
  LIBRARIES m4c0::parser
  )
