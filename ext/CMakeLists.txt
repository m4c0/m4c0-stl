add_library(bandit INTERFACE)
target_include_directories(bandit INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/bandit)
add_library(m4c0::ext::bandit ALIAS bandit)
