#include "check.hpp"
#include "m4c0/vulkan/begin_render_pass_continue.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/render_pass.hpp"

using namespace m4c0::vulkan::cmd;

void begin_render_pass_continue::now() const {
  VkCommandBufferInheritanceInfo inheritance {};
  inheritance.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  inheritance.framebuffer = m_framebuffer->pointer();
  inheritance.renderPass = m_render_pass->pointer();

  VkCommandBufferBeginInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  info.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
  info.pInheritanceInfo = &inheritance;
  check(vkBeginCommandBuffer(pointer(), &info));
}
