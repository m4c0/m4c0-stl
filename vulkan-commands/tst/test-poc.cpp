#include "m4c0/vulkan/begin_one_time_submit.hpp"
#include "m4c0/vulkan/begin_render_pass.hpp"
#include "m4c0/vulkan/begin_render_pass_continue.hpp"
#include "m4c0/vulkan/bind_descriptor_set.hpp"
#include "m4c0/vulkan/bind_index_buffer.hpp"
#include "m4c0/vulkan/bind_pipeline.hpp"
#include "m4c0/vulkan/bind_vertex_buffer.hpp"
#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/copy_buffer_to_image.hpp"
#include "m4c0/vulkan/draw.hpp"
#include "m4c0/vulkan/end_command_buffer.hpp"
#include "m4c0/vulkan/end_render_pass.hpp"
#include "m4c0/vulkan/execute_commands.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/pipeline.hpp"
#include "m4c0/vulkan/pipeline_barrier.hpp"
#include "m4c0/vulkan/push_constants.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/set_scissor.hpp"
#include "m4c0/vulkan/set_viewport.hpp"
#include "m4c0/vulkan/update_buffer.hpp"

using namespace m4c0::vulkan::cmd;

int main() {
  m4c0::vulkan::buffer b;
  m4c0::vulkan::framebuffer fb;
  m4c0::vulkan::render_pass rp;
  m4c0::vulkan::image img;
  m4c0::vulkan::pipeline p;

  VkCommandBuffer cb {};
  begin_one_time_submit(cb).now();

  image_memory_pipeline_barrier(cb).with_image(&img).from_host_to_transfer();
  image_memory_pipeline_barrier(cb).with_image(&img).from_transfer_to_fragment_shader();
  set_scissor(cb).with_size(3, 2).now();
  set_viewport(cb).with_size(3, 2).now();
  update_buffer(cb).now();
  copy_buffer_to_image(cb).now();

  end_command_buffer(cb).now();

  VkCommandBuffer cb2 {};
  auto base_rpc = base_render_pass_command<void>(cb2).with_framebuffer(&fb).with_render_pass(&rp);

  begin_render_pass_continue(base_rpc).now();

  begin_render_pass(base_rpc).with_clear_color(1, 1, 0, 0).now();
  end_render_pass(base_rpc).now();

  execute_commands(cb).add_command_buffer(cb2).now();

  struct {
  } complex_stuff;
  push_constants(cb).with_data_from(&complex_stuff).to_vertex_stage();
  bind_descriptor_set(cb).now();
  bind_pipeline(cb).with_pipeline(&p).now();
  bind_vertex_buffer(cb).with_buffer(&b).now();
  bind_index_buffer(cb).with_buffer(&b).now();
  draw(cb).now();
}
