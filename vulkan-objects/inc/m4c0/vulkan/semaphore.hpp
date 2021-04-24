#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkSemaphore_T;

namespace m4c0::vulkan {
  class semaphore : public details::nd_handle<VkSemaphore_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static semaphore create();
  };
}
