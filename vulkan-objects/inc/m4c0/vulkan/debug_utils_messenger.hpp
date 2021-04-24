#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkDebugUtilsMessengerEXT_T;

namespace m4c0::vulkan {
  class debug_utils_messenger : public details::nd_handle<VkDebugUtilsMessengerEXT_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static debug_utils_messenger create();
  };
}
