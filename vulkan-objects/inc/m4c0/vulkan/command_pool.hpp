#pragma once

#include "m4c0/vulkan/handle.hpp"

#include <vector>

using VkCommandPool = struct VkCommandPool_T *;

namespace m4c0::vulkan {
  struct command_pool : details::handle<VkCommandPool> {
    using handle::handle;
    [[nodiscard]] static command_pool create_resettable_for_queue_family(int qf);
  };
}
