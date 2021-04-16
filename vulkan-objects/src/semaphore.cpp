#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/semaphore.hpp"

using namespace m4c0::vulkan;

semaphore semaphore::create() {
  VkSemaphoreCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  return semaphore { details::safe_create_d<VkSemaphore>(vkCreateSemaphore, &info) };
}

template<>
void details::base_handle<VkSemaphore>::reset() {
  safe_destroy_d(vkDestroySemaphore, this);
}
