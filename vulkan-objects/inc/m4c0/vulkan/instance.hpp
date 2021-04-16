#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkInstance_T;

namespace m4c0::vulkan {
  struct instance : details::handle<VkInstance_T> {
    using handle::handle;
    [[nodiscard]] static instance create_for_app(const char * app_name);
  };
}
