#include "m4c0/vulkan/begin_one_time_submit.hpp"
#include "m4c0/vulkan/begin_render_pass.hpp"
#include "m4c0/vulkan/begin_render_pass_continue.hpp"
#include "m4c0/vulkan/copy_buffer_to_image.hpp"
#include "m4c0/vulkan/end_command_buffer.hpp"
#include "m4c0/vulkan/end_render_pass.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/pipeline_barrier.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/set_scissor.hpp"
#include "m4c0/vulkan/set_viewport.hpp"
#include "m4c0/vulkan/update_buffer.hpp"

using namespace m4c0::vulkan::cmd;

int main() {
  m4c0::vulkan::framebuffer fb;
  m4c0::vulkan::render_pass rp;
  m4c0::vulkan::image img;

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
  begin_render_pass_continue(cb2).with_render_pass(&rp).with_framebuffer(&fb).now();

  begin_render_pass(cb2).with_render_pass(&rp).with_framebuffer(&fb).with_clear_color(1, 1, 0, 0).now();
  end_render_pass(cb2).now();
}
