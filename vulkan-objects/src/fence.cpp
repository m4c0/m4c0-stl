#include "m4c0/vulkan/fence.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

#include <array>
#include <limits>

using namespace m4c0::vulkan;

fence fence::create_signaled() {
  VkFenceCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  return fence { details::safe_create_d<VkFence>(vkCreateFence, &info) };
}

template<>
void details::base_handle<VkFence_T>::reset() {
  safe_destroy_d(vkDestroyFence, this);
}

void fence::wait_and_reset() const {
  constexpr const auto timeout = std::numeric_limits<uint64_t>::max();
  const auto fences = std::array { pointer() };

  details::safe_call_d(vkWaitForFences, fences.size(), fences.data(), VK_TRUE, timeout);
  details::safe_call_d(vkResetFences, fences.size(), fences.data());
}
