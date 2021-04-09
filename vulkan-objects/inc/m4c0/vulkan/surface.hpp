#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkSurfaceKHR = struct VkSurfaceKHR_T *;

namespace m4c0::vulkan {
  using native_ptr_t = void *;

  struct surface : details::handle<VkSurfaceKHR> {
    using handle::handle;
    [[nodiscard]] static surface for_native_ptr(native_ptr_t);
  };
}
