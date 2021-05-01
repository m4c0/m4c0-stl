#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "m4c0/vulkan/surface_capabilities.hpp"

#include <algorithm>

using namespace m4c0::vulkan;

surface_capabilities::surface_capabilities(VkSurfaceCapabilitiesKHR sc) {
  m_data.make_new(sc);
}
surface_capabilities surface_capabilities::for_physical_device_and_surface(
    const physical_device * pd,
    const surface * s) {
  VkSurfaceCapabilitiesKHR cap {};
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pd->pointer(), s->pointer(), &cap);
  return surface_capabilities { cap };
}

extent_2d surface_capabilities::current_extent() const {
  return extent_2d { m_data->currentExtent.width, m_data->currentExtent.height };
}

unsigned surface_capabilities::normalize_height(unsigned h) const {
  if (m_data->currentExtent.height != std::numeric_limits<uint32_t>::max()) {
    return m_data->currentExtent.height;
  }

  return std::max(m_data->minImageExtent.height, std::min(m_data->maxImageExtent.height, h));
}
unsigned surface_capabilities::normalize_width(unsigned w) const {
  if (m_data->currentExtent.width != std::numeric_limits<uint32_t>::max()) {
    return m_data->currentExtent.width;
  }

  return std::max(m_data->minImageExtent.width, std::min(m_data->maxImageExtent.width, w));
}
