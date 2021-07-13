m4c0_add_library(
  TARGET m4c0-vulkan-actions
  ALIAS m4c0::vulkan::actions
  SOURCES
    src/allocate_command_buffers.cpp
    src/allocate_descriptor_sets.cpp
    src/bind_buffer_memory.cpp
    src/bind_image_memory.cpp
    src/device_wait_idle.cpp
    src/queue_present.cpp
    src/queue_submit.cpp
    src/update_descriptor_sets.cpp
  LIBRARIES
    m4c0::vulkan::objects
  )

m4c0_add_test(
  TARGET m4c0-test-vulkan-actions-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0::vulkan::actions
  )
