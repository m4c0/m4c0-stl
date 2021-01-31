add_executable(test-di test-di.cpp)
target_link_libraries(test-di PRIVATE m4c0::di m4c0::test)
add_test(di::base test-di)

add_executable(test-di-scopes test-di-scopes.cpp)
target_link_libraries(test-di-scopes PRIVATE m4c0::di m4c0::test)
add_test(di::scopes test-di-scopes)
