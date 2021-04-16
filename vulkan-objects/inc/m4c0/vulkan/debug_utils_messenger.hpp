#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkDebugUtilsMessengerEXT_T;

namespace m4c0::vulkan {
  struct debug_utils_messenger : details::nd_handle<VkDebugUtilsMessengerEXT_T> {
    using nd_handle::nd_handle;
    [[nodiscard]] static debug_utils_messenger create();
  };
}
