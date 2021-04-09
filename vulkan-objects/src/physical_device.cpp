#include "m4c0/log.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/safe_call.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "safe_calls.hpp"

#include <optional>
#include <sstream>

using namespace m4c0::vulkan;

static bool is_surface_compatible(VkPhysicalDevice pd, VkSurfaceKHR s) {
  uint32_t count {};

  vkGetPhysicalDeviceSurfaceFormatsKHR(pd, s, &count, nullptr);
  if (count == 0) return false;

  vkGetPhysicalDeviceSurfacePresentModesKHR(pd, s, &count, nullptr);
  if (count == 0) return false;

  VkPhysicalDeviceFeatures f {};
  vkGetPhysicalDeviceFeatures(pd, &f);
  return f.samplerAnisotropy == VK_TRUE;
}

static std::optional<int> get_queue_family(VkPhysicalDevice pd, VkSurfaceKHR s) {
  auto queues = details::unsafe_enumerate<VkQueueFamilyProperties>(vkGetPhysicalDeviceQueueFamilyProperties, pd);
  for (int idx = 0; idx < queues.size(); ++idx) {
    if ((queues[idx].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0) {
      continue;
    }
    if ((queues[idx].queueFlags & VK_QUEUE_TRANSFER_BIT) == 0) {
      continue;
    }

    VkBool32 surf_support {};
    vkGetPhysicalDeviceSurfaceSupportKHR(pd, idx, s, &surf_support);
    if (surf_support == VK_TRUE) {
      return idx;
    }
  }
  return std::nullopt;
}

static void log_rejected_device(VkPhysicalDevice pd, const char * reason) {
  VkPhysicalDeviceProperties props {};
  vkGetPhysicalDeviceProperties(pd, &props);

  const char * name = static_cast<const char *>(props.deviceName);

  std::ostringstream msg {};
  msg << "Rejecting device [" << name << "] - reason: " << reason;
  m4c0::log::warning(msg.str().c_str());
}
static void log_device_count(int n) {
  std::ostringstream msg {};
  msg << "Found " << n << " Vulkan physical devices";
  m4c0::log::info(msg.str().c_str());
}

physical_device physical_device::best_for(const surface * surf) {
  VkSurfaceKHR s = surf->pointer();
  VkInstance i = loader::get_instance();
  auto list = details::safe_enumerate<VkPhysicalDevice>(vkEnumeratePhysicalDevices, i);
  log_device_count(list.size());

  for (VkPhysicalDevice pd : list) {
    auto qf = get_queue_family(pd, s);
    if (!qf) {
      log_rejected_device(pd, "Missing compatible queue family");
      continue;
    }

    if (!is_surface_compatible(pd, s)) {
      log_rejected_device(pd, "Missing compatible surface");
      continue;
    }

    physical_device res { pd, qf.value() };

    VkPhysicalDeviceProperties props {};
    vkGetPhysicalDeviceProperties(pd, &props);

    const char * name = static_cast<const char *>(props.deviceName);

    using namespace std::literals::string_literals;
    std::string msg = "Using device: "s + name;
    m4c0::log::info(msg.c_str());

    return res;
  }
  throw std::runtime_error("No suitable Vulkan device found");
}
