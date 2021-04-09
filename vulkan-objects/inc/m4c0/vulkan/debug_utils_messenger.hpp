#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkDebugUtilsMessengerEXT = struct VkDebugUtilsMessengerEXT_T *;

namespace m4c0::vulkan {
  struct debug_utils_messenger : details::handle<VkDebugUtilsMessengerEXT> {
    using handle::handle;
    [[nodiscard]] static debug_utils_messenger create();
  };
}
