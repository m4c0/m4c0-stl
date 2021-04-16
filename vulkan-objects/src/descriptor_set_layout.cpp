#include "m4c0/vulkan/descriptor_set_layout.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

using namespace m4c0::vulkan;

using list = std::vector<VkDescriptorSetLayoutBinding>;
class descriptor_set_layout::builder::set_layout_bindings : public list {};

descriptor_set_layout descriptor_set_layout::builder::build() const {
  VkDescriptorSetLayoutCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  info.bindingCount = m_bindings->size();
  info.pBindings = m_bindings->data();
  return descriptor_set_layout { details::safe_create_d<VkDescriptorSetLayout>(vkCreateDescriptorSetLayout, &info) };
}

template<>
void details::base_handle<VkDescriptorSetLayout_T>::reset() {
  safe_destroy_d(vkDestroyDescriptorSetLayout, this);
}

descriptor_set_layout::builder::builder() {
  m_bindings.make_new();
}

static void create_binding(list * l, VkDescriptorType type, VkShaderStageFlags stage_flags) {
  VkDescriptorSetLayoutBinding b {};
  b.binding = l->size();
  b.descriptorType = type;
  b.descriptorCount = 1;
  b.stageFlags = stage_flags;
  l->push_back(b);
};
descriptor_set_layout::builder & descriptor_set_layout::builder::add_fragment_sampler_binding() {
  create_binding(m_bindings.get(), VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT);
  return *this;
}
descriptor_set_layout::builder & descriptor_set_layout::builder::add_fragment_uniform_binding() {
  create_binding(m_bindings.get(), VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT);
  return *this;
}
descriptor_set_layout::builder & descriptor_set_layout::builder::add_vertex_uniform_binding() {
  create_binding(m_bindings.get(), VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
  return *this;
}
descriptor_set_layout::builder & descriptor_set_layout::builder::add_vertex_uniform_dynamic_binding() {
  create_binding(m_bindings.get(), VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, VK_SHADER_STAGE_VERTEX_BIT);
  return *this;
}
