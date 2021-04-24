#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkInstance_T;

namespace m4c0::vulkan {
  class instance : public details::handle<VkInstance_T> {
  public:
    using handle::handle;
    [[nodiscard]] static instance create_for_app(const char * app_name);
  };
}
