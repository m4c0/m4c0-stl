m4c0_add_library(
  TARGET m4c0-vulkan
  ALIAS m4c0::vulkan
  SOURCES
    src/debug_utils_messenger.cpp
    src/instance.cpp
    src/safe_calls.cpp
  LIBRARIES
    m4c0::ext::volk
    m4c0::log
  )
target_compile_definitions(m4c0-vulkan PRIVATE M4C0_VULKAN_SURFACE_EXTENSION_NAME="Dummy")

m4c0_add_test(
  TARGET m4c0-test-vulkan-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0::vulkan)
