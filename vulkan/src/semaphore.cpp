#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/semaphore.hpp"
#include "safe_calls.hpp"

using namespace m4c0::vulkan;

semaphore semaphore::create() {
  VkSemaphoreCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  return semaphore { details::safe_create<VkSemaphore>(vkCreateSemaphore, loader::get_device(), &info) };
}

template<>
void details::handle<VkSemaphore>::reset() {
  vkDestroySemaphore(loader::get_device(), pointer(), nullptr);
}
