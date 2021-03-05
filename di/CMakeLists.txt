m4c0_add_library(
  TARGET m4c0-di
  ALIAS m4c0::di
  SOURCES
    src/config.cpp
    src/injector.cpp
    src/type_id.cpp
  LIBRARIES m4c0::core
  )

m4c0_add_test(
  ALIAS m4c0::di::base
  TARGET m4c0-test-di
  SOURCES tst/test-di.cpp
  LIBRARIES m4c0::di m4c0::test)

m4c0_add_test(
  ALIAS m4c0::di::scopes
  TARGET m4c0-test-di-scopes
  SOURCES tst/test-di-scopes.cpp
  LIBRARIES m4c0::di m4c0::test)
