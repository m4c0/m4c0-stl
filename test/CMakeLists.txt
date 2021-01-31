add_library(m4c0-test INTERFACE)
target_include_directories(m4c0-test INTERFACE inc)
target_link_libraries(m4c0-test INTERFACE m4c0::ext::bandit)

add_library(m4c0::test ALIAS m4c0-test)

