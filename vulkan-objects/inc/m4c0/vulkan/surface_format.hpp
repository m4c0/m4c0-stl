#pragma once

#include "m4c0/pimpl.hpp"

struct VkSurfaceFormatKHR;

namespace m4c0::vulkan {
  class physical_device;
  class surface;

  class surface_format {
    m4c0::pimpl<VkSurfaceFormatKHR> m_sfmt;

    explicit surface_format(VkSurfaceFormatKHR sfmt);

  public:
    [[nodiscard]] static surface_format best_from_device_and_surface(const physical_device * pd, const surface * s);

    [[nodiscard]] constexpr const VkSurfaceFormatKHR * pointer() const {
      return m_sfmt.get();
    }
  };
}
