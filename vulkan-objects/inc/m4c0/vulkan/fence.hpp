#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkFence = struct VkFence_T *;

namespace m4c0::vulkan {
  struct fence : details::handle<VkFence> {
    using handle::handle;
    [[nodiscard]] static fence create_signaled();

    void wait_and_reset() const;
  };
}
