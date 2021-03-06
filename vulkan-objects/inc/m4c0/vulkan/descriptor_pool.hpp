#pragma once

#include "m4c0/pimpl.hpp"
#include "m4c0/vulkan/handle.hpp"

struct VkDescriptorPool_T;

namespace m4c0::vulkan {
  class descriptor_pool : public details::nd_handle<VkDescriptorPool_T> {
  public:
    class builder {
      class pool_sizes;

      unsigned m_max_sets;
      pimpl<pool_sizes> m_pool_sizes {};

    public:
      builder();

      [[nodiscard]] builder & with_max_sets(unsigned ms) {
        m_max_sets = ms;
        return *this;
      }
      [[nodiscard]] builder & add_uniform_buffer_type(unsigned qty);
      [[nodiscard]] builder & add_uniform_buffer_dynamic_type(unsigned qty);
      [[nodiscard]] builder & add_combined_image_sampler_type(unsigned qty);

      [[nodiscard]] descriptor_pool build() const;
    };

    using nd_handle::nd_handle;
  };
}
