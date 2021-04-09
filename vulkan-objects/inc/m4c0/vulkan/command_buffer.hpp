#pragma once

#include "m4c0/vulkan/handle.hpp"
using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::vulkan {
  struct command_buffer : details::handle<VkCommandBuffer> {
    using handle::handle;
    explicit constexpr command_buffer(VkCommandBuffer p) : handle(p) {
    }
  };
}
