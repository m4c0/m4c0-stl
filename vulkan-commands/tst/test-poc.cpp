#include "m4c0/vulkan/begin_one_time_submit.hpp"
#include "m4c0/vulkan/begin_render_pass.hpp"
#include "m4c0/vulkan/begin_render_pass_continue.hpp"
#include "m4c0/vulkan/end_command_buffer.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/render_pass.hpp"

using namespace m4c0::vulkan::cmd;

int main() {
  m4c0::vulkan::framebuffer fb;
  m4c0::vulkan::render_pass rp;

  VkCommandBuffer cb {};
  begin_one_time_submit(cb).now();
  end_command_buffer(cb).now();

  VkCommandBuffer cb2 {};
  begin_render_pass_continue(cb2).with_render_pass(&rp).with_framebuffer(&fb).now();

  begin_render_pass(cb2).with_render_pass(&rp).with_framebuffer(&fb).with_clear_color(1, 1, 0, 0).now();
}
