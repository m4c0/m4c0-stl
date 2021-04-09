#pragma once

#include "m4c0/pimpl.hpp"
#include "m4c0/vulkan/handle.hpp"

using VkPipelineLayout = struct VkPipelineLayout_T *;

namespace m4c0::vulkan {
  class descriptor_set_layout;

  struct pipeline_layout : details::handle<VkPipelineLayout> {
    class builder {
      class set_layouts;
      class push_constants;

      pimpl<set_layouts> m_descriptor_set_layouts {};
      pimpl<push_constants> m_push_constants {};

    public:
      builder();

      [[nodiscard]] builder & add_descriptor_set_layout(const descriptor_set_layout *);
      [[nodiscard]] builder & add_vertex_push_constant_with_size_and_offset(unsigned size, unsigned offset);
      [[nodiscard]] pipeline_layout build();
    };

    using handle::handle;
  };
}
