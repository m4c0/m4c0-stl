#include "m4c0/vulkan/begin_one_time_submit.hpp"
#include "m4c0/vulkan/begin_render_pass_continue.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/render_pass.hpp"

using namespace m4c0::vulkan::cmd;

int main() {
  m4c0::vulkan::framebuffer fb;
  m4c0::vulkan::render_pass rp;

  VkCommandBuffer cb {};

  one_time_submit(cb).begin();
  render_pass_continue(cb).with_render_pass(&rp).with_framebuffer(&fb).begin();
}
