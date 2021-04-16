#pragma once

#include "m4c0/vulkan/handle.hpp"
struct VkDescriptorSet_T;

namespace m4c0::vulkan {
  class image_view;
  class sampler;
}

namespace m4c0::vulkan::actions {
  class write_image_to_descriptor_set {
    using desc_set_t = details::pointer_t<VkDescriptorSet_T>;

    const image_view * m_image_view;
    const sampler * m_sampler;
    desc_set_t m_descriptor_set;
    unsigned m_binding;

  public:
    [[nodiscard]] constexpr write_image_to_descriptor_set & with_destination_set(desc_set_t ds) noexcept {
      m_descriptor_set = ds;
      return *this;
    }
    [[nodiscard]] constexpr write_image_to_descriptor_set & with_binding(unsigned b) noexcept {
      m_binding = b;
      return *this;
    }
    [[nodiscard]] constexpr write_image_to_descriptor_set & with_image_view(const image_view * iv) noexcept {
      m_image_view = iv;
      return *this;
    }
    [[nodiscard]] constexpr write_image_to_descriptor_set & with_sampler(const sampler * s) noexcept {
      m_sampler = s;
      return *this;
    }
    void now() const;
  };
}
