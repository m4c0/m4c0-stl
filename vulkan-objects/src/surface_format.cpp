#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "m4c0/vulkan/surface_format.hpp"

using namespace m4c0::vulkan;

static VkSurfaceFormatKHR get_best_surface_format(VkPhysicalDevice pd, VkSurfaceKHR surf) {
  auto formats = details::safe_enumerate<VkSurfaceFormatKHR>(vkGetPhysicalDeviceSurfaceFormatsKHR, pd, surf);
  for (const auto & fmt : formats) {
    if ((fmt.format == VK_FORMAT_B8G8R8A8_SRGB) && (fmt.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)) {
      return fmt;
    }
  }
  for (const auto & fmt : formats) {
    if ((fmt.format == VK_FORMAT_B8G8R8A8_SRGB)) {
      return fmt;
    }
  }
  return *formats.begin();
}

surface_format surface_format::best_from_device_and_surface(const physical_device * pd, const surface * s) {
  return surface_format { get_best_surface_format(pd->pointer(), s->pointer()) };
}

surface_format::surface_format(VkSurfaceFormatKHR sfmt) {
  m_sfmt.make_new(sfmt);
}
