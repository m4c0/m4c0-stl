#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkSurfaceKHR_T;

namespace m4c0::vulkan {
  class native_provider;

  class surface : public details::nd_handle<VkSurfaceKHR_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static surface for_native_ptr(const native_provider * np);
  };
}
