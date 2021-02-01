add_executable(m4c0-test-function test-function.cpp)
target_link_libraries(m4c0-test-function PRIVATE m4c0::core m4c0::test)
add_test(m4c0::core::function m4c0-test-function)

add_executable(m4c0-test-pimpl test-pimpl.cpp)
target_link_libraries(m4c0-test-pimpl PRIVATE m4c0::core m4c0::test)
add_test(m4c0::core::pimpl m4c0-test-pimpl)
