#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkDevice = struct VkDevice_T *;

namespace m4c0::vulkan {
  class physical_device;

  struct device : details::handle<VkDevice> {
    using handle::handle;

    [[nodiscard]] static device create_for_physical_device(const physical_device * pd);

    void wait_idle() const noexcept;
  };
}
