add_library(m4c0-bandit INTERFACE)
target_include_directories(m4c0-bandit INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/bandit)
add_library(m4c0::ext::bandit ALIAS m4c0-bandit)
