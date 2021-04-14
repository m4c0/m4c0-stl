#pragma once

#include "m4c0/pimpl.hpp"

struct VkSurfaceCapabilitiesKHR;

namespace m4c0::vulkan {
  class physical_device;
  class surface;

  class surface_capabilities {
    pimpl<VkSurfaceCapabilitiesKHR> m_data;

    explicit surface_capabilities(VkSurfaceCapabilitiesKHR);

  public:
    [[nodiscard]] static surface_capabilities for_physical_device_and_surface(
        const physical_device * pd,
        const surface * s);

    [[nodiscard]] unsigned normalize_height(unsigned h) const;
    [[nodiscard]] unsigned normalize_width(unsigned w) const;
  };
}
