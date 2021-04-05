#include "m4c0/vulkan/device.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "safe_calls.hpp"

#include <array>

using namespace m4c0::vulkan;

static auto create_queue_info(uint32_t index) {
  static const std::array<float, 1> queues { 1.0 };

  VkDeviceQueueCreateInfo queue_create_info {};
  queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_create_info.queueFamilyIndex = index;
  queue_create_info.queueCount = queues.size();
  queue_create_info.pQueuePriorities = queues.data();
  return queue_create_info;
}

static VkDevice create_device(VkPhysicalDevice pd, int qf) {
  static const std::array device_extensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

  auto queues = std::array { create_queue_info(qf) };

  VkPhysicalDeviceFeatures deviceFeatures {};
  deviceFeatures.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo create_info {};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.pQueueCreateInfos = queues.data();
  create_info.queueCreateInfoCount = queues.size();
  create_info.pEnabledFeatures = &deviceFeatures;
  create_info.ppEnabledExtensionNames = device_extensions.data();
  create_info.enabledExtensionCount = device_extensions.size();
  create_info.enabledLayerCount = 0; // device layer is legacy

  return details::safe_create<VkDevice>(vkCreateDevice, pd, &create_info);
}

static VkQueue get_queue(VkDevice d, int qf) {
  VkQueue q {};
  vkGetDeviceQueue(d, qf, 0, &q);
  return q;
}

device device::create_for_physical_device(const physical_device * pd) {
  VkDevice d = create_device(pd->pointer(), pd->unified_queue_family());
  loader::load_device(d);
  return device { d, get_queue(d, pd->unified_queue_family()) };
}

template<>
void details::handle<VkDevice>::reset() {
  vkDestroyDevice(pointer(), nullptr);
}

void device::wait_idle() const noexcept {
  vkDeviceWaitIdle(pointer());
}
