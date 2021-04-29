m4c0_add_library(
  TARGET m4c0-fuji
  ALIAS m4c0::fuji
  LIBRARIES
    m4c0::vulkan
  SOURCES
    src/device_context.cpp
    src/depth_buffer.cpp
    src/frame_context.cpp
    src/main_loop.cpp
    src/swapchain_context.cpp
  )

if(NOT(CMAKE_SYSTEM_NAME STREQUAL "iOS"))
  m4c0_add_test(
    TARGET m4c0-fuji-test-poc
    SOURCES tst/test-poc.cpp
    LIBRARIES m4c0::fuji
    )
endif()
