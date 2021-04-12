#include "check.hpp"
#include "m4c0/vulkan/bind_pipeline.hpp"
#include "m4c0/vulkan/pipeline.hpp"

void m4c0::vulkan::cmd::bind_pipeline::now() const {
  vkCmdBindPipeline(pointer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline->pointer());
}
