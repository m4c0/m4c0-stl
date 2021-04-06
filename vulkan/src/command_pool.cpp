#include "m4c0/vulkan/command_pool.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "safe_calls.hpp"

#include <array>

using namespace m4c0::vulkan;

command_pool command_pool::create_resettable_for_queue_family(int qf) {
  VkCommandPoolCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  info.queueFamilyIndex = qf;
  return command_pool { details::safe_create_d<VkCommandPool>(vkCreateCommandPool, &info) };
}

template<>
void details::handle<VkCommandPool>::reset() {
  vkDestroyCommandPool(loader::get_device(), pointer(), nullptr);
}

std::vector<VkCommandBuffer> command_pool::allocate(int count, bool primary) {
  VkCommandBufferAllocateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.commandPool = pointer();
  info.commandBufferCount = count;
  info.level = primary ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;

  std::vector<VkCommandBuffer> res { static_cast<std::size_t>(count) };
  details::safe_call_d(vkAllocateCommandBuffers, &info, res.data());
  return res;
}
