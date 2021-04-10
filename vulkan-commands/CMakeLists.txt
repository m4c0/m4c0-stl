m4c0_add_library(
  TARGET m4c0-vulkan-commands
  ALIAS m4c0::vulkan::commands
  SOURCES
    src/begin_one_time_submit.cpp
    src/begin_render_pass_continue.cpp
  LIBRARIES
    m4c0::log
    m4c0::vulkan::objects
  )

m4c0_add_test(
  TARGET m4c0-test-vulkan-commands-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0::vulkan::commands
  )
