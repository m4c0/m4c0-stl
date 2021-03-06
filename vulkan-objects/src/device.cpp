#include "m4c0/vulkan/device.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

#include <array>

using namespace m4c0::vulkan;

static VkDevice create_device(VkPhysicalDevice pd, int qf) {
  static const std::array device_extensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
  static const std::array<float, 1> queue_prioritiess { 1.0 };

  VkDeviceQueueCreateInfo queue_create_info {};
  queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_create_info.queueFamilyIndex = qf;
  queue_create_info.queueCount = queue_prioritiess.size();
  queue_create_info.pQueuePriorities = queue_prioritiess.data();

  auto queues = std::array { queue_create_info };
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

device device::create_for_physical_device(const physical_device * pd) {
  VkDevice d = create_device(pd->pointer(), pd->unified_queue_family());
  loader::load_device(d);
  return device { d };
}

template<>
void details::base_handle<VkDevice_T>::reset() {
  vkDestroyDevice(pointer(), nullptr);
}
