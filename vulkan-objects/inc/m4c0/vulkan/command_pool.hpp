#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkCommandPool_T;

namespace m4c0::vulkan {
  struct command_pool : details::nd_handle<VkCommandPool_T> {
    using nd_handle::nd_handle;
    [[nodiscard]] static command_pool create_resettable_for_queue_family(int qf);
  };
}
