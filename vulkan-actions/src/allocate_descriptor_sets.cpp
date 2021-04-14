#include "m4c0/vulkan/allocate_descriptor_sets.hpp"
#include "m4c0/vulkan/descriptor_pool.hpp"
#include "m4c0/vulkan/descriptor_set_layout.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

VkDescriptorSet m4c0::vulkan::actions::allocate_descriptor_sets::now() const {
  VkDescriptorSetLayout layout = m_layout->pointer();

  VkDescriptorSetAllocateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  info.descriptorPool = m_pool->pointer();
  info.descriptorSetCount = 1;
  info.pSetLayouts = &layout;

  VkDescriptorSet result {};
  details::safe_call_d(vkAllocateDescriptorSets, &info, &result);
  return result;
}
