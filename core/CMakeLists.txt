add_library(m4c0-core INTERFACE)
target_compile_features(m4c0-core INTERFACE cxx_std_20)
target_include_directories(m4c0-core INTERFACE inc)

add_library(m4c0::core ALIAS m4c0-core)

add_subdirectory(tst)
