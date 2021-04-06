#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkSemaphore = struct VkSemaphore_T *;

namespace m4c0::vulkan {
  struct semaphore : details::handle<VkSemaphore> {
    using handle::handle;
    [[nodiscard]] static semaphore create();
  };
}
