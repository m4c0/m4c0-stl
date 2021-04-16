#pragma once

#include "m4c0/pimpl.hpp"
#include "m4c0/vulkan/handle.hpp"

struct VkDescriptorSetLayout_T;

namespace m4c0::vulkan {
  struct descriptor_set_layout : details::nd_handle<VkDescriptorSetLayout_T> {
    class builder {
      class set_layout_bindings;
      pimpl<set_layout_bindings> m_bindings {};

    public:
      builder();

      [[nodiscard]] builder & add_fragment_sampler_binding();
      [[nodiscard]] builder & add_fragment_uniform_binding();
      [[nodiscard]] builder & add_vertex_uniform_binding();
      [[nodiscard]] builder & add_vertex_uniform_dynamic_binding();

      [[nodiscard]] descriptor_set_layout build() const;
    };

    using nd_handle::nd_handle;
  };
}
