m4c0_add_library(
  TARGET m4c0-vulkan-commands
  SOURCES
    src/begin_one_time_submit.cpp
    src/begin_render_pass.cpp
    src/begin_render_pass_continue.cpp
    src/bind_descriptor_set.cpp
    src/bind_index_buffer.cpp
    src/bind_pipeline.cpp
    src/bind_vertex_buffer.cpp
    src/copy_buffer_to_image.cpp
    src/draw.cpp
    src/end_command_buffer.cpp
    src/end_render_pass.cpp
    src/execute_commands.cpp
    src/pipeline_barrier.cpp
    src/push_constants.cpp
    src/set_scissor.cpp
    src/set_viewport.cpp
    src/update_buffer.cpp
  LIBRARIES
    m4c0-log
    m4c0-vulkan-objects
  )

m4c0_add_test(
  TARGET m4c0-test-vulkan-commands-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0-vulkan-commands
  )
