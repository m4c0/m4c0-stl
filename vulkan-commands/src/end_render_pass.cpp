#include "check.hpp"
#include "m4c0/vulkan/end_render_pass.hpp"

using namespace m4c0::vulkan::cmd;

void end_render_pass::now() const {
  vkCmdEndRenderPass(pointer());
}
