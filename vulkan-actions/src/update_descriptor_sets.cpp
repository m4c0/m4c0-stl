#include "m4c0/vulkan/image_view.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/sampler.hpp"
#include "m4c0/vulkan/update_descriptor_sets.hpp"

void m4c0::vulkan::actions::write_image_to_descriptor_set::now() const {
  VkDescriptorImageInfo ii {};
  ii.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  ii.imageView = m_image_view->pointer();
  ii.sampler = m_sampler->pointer();

  VkWriteDescriptorSet w {};
  w.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  w.dstSet = m_descriptor_set;
  w.dstBinding = m_binding;
  w.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  w.descriptorCount = 1;
  w.pImageInfo = &ii;
  vkUpdateDescriptorSets(m4c0::vulkan::loader::get_device(), 1, &w, 0, nullptr);
}
