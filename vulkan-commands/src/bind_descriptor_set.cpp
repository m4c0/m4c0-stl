#include "check.hpp"
#include "m4c0/vulkan/bind_descriptor_set.hpp"
#include "m4c0/vulkan/pipeline_layout.hpp"

void m4c0::vulkan::cmd::bind_descriptor_set::now() const {
  vkCmdBindDescriptorSets(
      pointer(),
      VK_PIPELINE_BIND_POINT_GRAPHICS,
      m_pipeline_layout->pointer(),
      m_first_set,
      1,
      &m_descriptor_set,
      0,
      nullptr);
}
