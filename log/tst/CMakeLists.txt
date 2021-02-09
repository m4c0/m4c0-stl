# This checks if all symbols are correct
add_executable(m4c0-test-log-link test-log-link.cpp)
target_link_libraries(m4c0-test-log-link PRIVATE m4c0::log)
