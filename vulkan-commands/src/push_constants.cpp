#include "check.hpp"
#include "m4c0/vulkan/pipeline_layout.hpp"
#include "m4c0/vulkan/push_constants.hpp"

void m4c0::vulkan::cmd::push_constants::to_vertex_stage() const {
  vkCmdPushConstants(pointer(), m_pipeline_layout->pointer(), VK_SHADER_STAGE_VERTEX_BIT, m_offset, m_length, m_data);
}
