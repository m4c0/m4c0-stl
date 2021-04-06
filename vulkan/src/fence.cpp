#include "m4c0/vulkan/fence.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "safe_calls.hpp"

using namespace m4c0::vulkan;

fence fence::create_signaled() {
  VkFenceCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  return fence { details::safe_create<VkFence>(vkCreateFence, loader::get_device(), &info) };
}

template<>
void details::handle<VkFence>::reset() {
  vkDestroyFence(loader::get_device(), pointer(), nullptr);
}
