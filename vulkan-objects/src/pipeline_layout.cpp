#include "m4c0/vulkan/descriptor_set_layout.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/pipeline_layout.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

#include <vector>

using namespace m4c0::vulkan;

struct pipeline_layout::builder::push_constants : public std::vector<VkPushConstantRange> {};
struct pipeline_layout::builder::set_layouts : public std::vector<VkDescriptorSetLayout> {};

pipeline_layout pipeline_layout::builder::build() {
  VkPipelineLayoutCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  info.pushConstantRangeCount = m_push_constants->size();
  info.pPushConstantRanges = m_push_constants->data();
  info.setLayoutCount = m_descriptor_set_layouts->size();
  info.pSetLayouts = m_descriptor_set_layouts->data();
  return pipeline_layout { details::safe_create_d<VkPipelineLayout>(vkCreatePipelineLayout, &info) };
}

template<>
void details::handle<VkPipelineLayout>::reset() {
  vkDestroyPipelineLayout(loader::get_device(), pointer(), nullptr);
}

pipeline_layout::builder::builder() {
  m_descriptor_set_layouts.make_new();
  m_push_constants.make_new();
}

pipeline_layout::builder & pipeline_layout::builder::add_descriptor_set_layout(const descriptor_set_layout * dsl) {
  m_descriptor_set_layouts->push_back(dsl->pointer());
  return *this;
}
pipeline_layout::builder & pipeline_layout::builder::add_vertex_push_constant_with_size_and_offset(
    unsigned size,
    unsigned offset) {
  VkPushConstantRange pc {};
  pc.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  pc.offset = offset;
  pc.size = size;
  m_push_constants->push_back(pc);
  return *this;
}
