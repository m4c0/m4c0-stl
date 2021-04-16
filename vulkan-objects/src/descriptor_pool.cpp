#include "m4c0/vulkan/descriptor_pool.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

using namespace m4c0::vulkan;

class descriptor_pool::builder::pool_sizes : public std::vector<VkDescriptorPoolSize> {};

descriptor_pool descriptor_pool::builder::build() const {
  VkDescriptorPoolCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  info.maxSets = m_max_sets;
  info.pPoolSizes = m_pool_sizes->data();
  info.poolSizeCount = m_pool_sizes->size();
  return descriptor_pool { details::safe_create_d<VkDescriptorPool>(vkCreateDescriptorPool, &info) };
}

template<>
void details::base_handle<VkDescriptorPool>::reset() {
  safe_destroy_d(vkDestroyDescriptorPool, this);
}

descriptor_pool::builder::builder() : m_max_sets(0) {
  m_pool_sizes.make_new();
}

static VkDescriptorPoolSize descriptor_pool_size(VkDescriptorType type, unsigned qty) {
  VkDescriptorPoolSize ps {};
  ps.type = type;
  ps.descriptorCount = qty;
  return ps;
};
descriptor_pool::builder & descriptor_pool::builder::add_combined_image_sampler_type(unsigned qty) {
  m_pool_sizes->push_back(descriptor_pool_size(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, qty));
  return *this;
}
descriptor_pool::builder & descriptor_pool::builder::add_uniform_buffer_dynamic_type(unsigned qty) {
  m_pool_sizes->push_back(descriptor_pool_size(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, qty));
  return *this;
}
descriptor_pool::builder & descriptor_pool::builder::add_uniform_buffer_type(unsigned qty) {
  m_pool_sizes->push_back(descriptor_pool_size(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, qty));
  return *this;
}
