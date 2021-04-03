#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkInstance = struct VkInstance_T *;

namespace m4c0::vulkan {
  struct instance : details::handle<VkInstance> {
    using handle::handle;
    [[nodiscard]] static instance create_for_app(const char * app_name);
  };
}
