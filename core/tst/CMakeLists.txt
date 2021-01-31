add_executable(test-function test-function.cpp)
target_link_libraries(test-function PRIVATE m4c0::core m4c0::test)
add_test(core::function test-function)

add_executable(test-pimpl test-pimpl.cpp)
target_link_libraries(test-pimpl PRIVATE m4c0::core m4c0::test)
add_test(core::pimpl test-pimpl)
