#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkSemaphore_T;

namespace m4c0::vulkan {
  struct semaphore : details::nd_handle<VkSemaphore_T> {
    using nd_handle::nd_handle;
    [[nodiscard]] static semaphore create();
  };
}
