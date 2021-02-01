add_executable(m4c0-test-di test-di.cpp)
target_link_libraries(m4c0-test-di PRIVATE m4c0::di m4c0::test)
add_test(di::base m4c0-test-di)

add_executable(m4c0-test-di-scopes test-di-scopes.cpp)
target_link_libraries(m4c0-test-di-scopes PRIVATE m4c0::di m4c0::test)
add_test(di::scopes m4c0-test-di-scopes)
