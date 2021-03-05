m4c0_add_test(
  ALIAS m4c0::di::base
  TARGET m4c0-test-di
  SOURCES test-di.cpp
  LIBRARIES m4c0::di m4c0::test)

m4c0_add_test(
  ALIAS m4c0::di::scopes
  TARGET m4c0-test-di-scopes
  SOURCES test-di-scopes.cpp
  LIBRARIES m4c0::di m4c0::test)
