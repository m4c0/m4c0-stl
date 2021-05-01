#pragma once

#include "m4c0/pimpl.hpp"
#include "m4c0/vulkan/extent_2d.hpp"

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

    [[nodiscard]] extent_2d current_extent() const;

    [[nodiscard]] unsigned normalize_height(unsigned h) const;
    [[nodiscard]] unsigned normalize_width(unsigned w) const;
    [[nodiscard]] extent_2d normalize_extent(extent_2d e) const {
      return { normalize_width(e.width()), normalize_height(e.height()) };
    }
  };
}
