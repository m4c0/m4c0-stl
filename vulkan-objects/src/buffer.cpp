#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

using namespace m4c0::vulkan;

static auto create_info_for_size(unsigned size) {
  VkBufferCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  info.size = size;
  info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  return info;
}

buffer buffer::create_transfer_source_with_size(unsigned int size) {
  auto info = create_info_for_size(size);
  info.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  return buffer { details::safe_create_d<VkBuffer>(vkCreateBuffer, &info) };
}
buffer buffer::create_vertex_buffer_with_size(unsigned int size) {
  auto info = create_info_for_size(size);
  info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  return buffer { details::safe_create_d<VkBuffer>(vkCreateBuffer, &info) };
}

template<>
void details::handle<VkBuffer>::reset() {
  safe_destroy_d(vkDestroyBuffer, this);
}

memory_requirements buffer::memory_requirements() const {
  VkMemoryRequirements res {};
  vkGetBufferMemoryRequirements(m4c0::vulkan::loader::get_device(), pointer(), &res);
  return vulkan::memory_requirements { res };
}
