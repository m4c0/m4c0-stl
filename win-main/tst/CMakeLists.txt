add_executable(m4c0-test-win-main-link WIN32 dummy.cpp)
target_link_libraries(m4c0-test-win-main-link PRIVATE m4c0::win::main)
