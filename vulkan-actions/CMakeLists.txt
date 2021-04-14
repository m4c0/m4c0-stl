m4c0_add_library(
  TARGET m4c0-vulkan-actions
  ALIAS m4c0::vulkan::actions
  SOURCES
    src/allocate_command_buffers.cpp
    src/device_wait_idle.cpp
    src/queue_present.cpp
  LIBRARIES
    m4c0::vulkan::objects
  )

if(NOT(CMAKE_SYSTEM_NAME STREQUAL "iOS"))
  m4c0_add_test(
    TARGET m4c0-test-vulkan-actions-poc
    SOURCES tst/test-poc.cpp
    LIBRARIES m4c0::vulkan::actions
    )
endif()
