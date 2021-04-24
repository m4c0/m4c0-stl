#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkDevice_T;

namespace m4c0::vulkan {
  class physical_device;

  class device : public details::handle<VkDevice_T> {
  public:
    using handle::handle;

    [[nodiscard]] static device create_for_physical_device(const physical_device * pd);
  };
}
