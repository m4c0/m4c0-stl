#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkBuffer = struct VkBuffer_T *;

namespace m4c0::vulkan {
  struct memory_requirements;

  struct buffer : details::handle<VkBuffer> {
    using handle::handle;
    [[nodiscard]] static buffer create_transfer_source_with_size(unsigned size);
    [[nodiscard]] static buffer create_vertex_buffer_with_size(unsigned size);

    [[nodiscard]] memory_requirements memory_requirements() const;
  };
}
