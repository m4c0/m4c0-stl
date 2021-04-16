#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkSurfaceKHR_T;

namespace m4c0::vulkan {
  using native_ptr_t = void *;

  struct surface : details::nd_handle<VkSurfaceKHR_T> {
    using nd_handle::nd_handle;
    [[nodiscard]] static surface for_native_ptr(native_ptr_t);
  };
}
