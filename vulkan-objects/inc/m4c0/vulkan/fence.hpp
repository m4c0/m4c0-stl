#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkFence_T;

namespace m4c0::vulkan {
  class fence : public details::nd_handle<VkFence_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static fence create_signaled();

    void wait_and_reset() const;
  };
}
