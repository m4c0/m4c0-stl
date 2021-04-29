#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkBuffer_T;

namespace m4c0::vulkan {
  class memory_requirements;

  class buffer : public details::nd_handle<VkBuffer_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static buffer create_transfer_source_with_size(unsigned size);
    [[nodiscard]] static buffer create_vertex_buffer_with_size(unsigned size);

    [[nodiscard]] memory_requirements memory_requirements() const;
  };
}
