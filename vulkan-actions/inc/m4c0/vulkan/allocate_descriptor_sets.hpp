#pragma once

#include <vector>

using VkDescriptorSet = struct VkDescriptorSet_T *;

namespace m4c0::vulkan {
  class descriptor_pool;
  class descriptor_set_layout;
}

namespace m4c0::vulkan::actions {
  class allocate_descriptor_sets {
    const descriptor_pool * m_pool;
    const descriptor_set_layout * m_layout;

  public:
    [[nodiscard]] constexpr allocate_descriptor_sets & with_pool(const descriptor_pool * p) noexcept {
      m_pool = p;
      return *this;
    }
    [[nodiscard]] constexpr allocate_descriptor_sets & with_set_layout(const descriptor_set_layout * l) noexcept {
      m_layout = l;
      return *this;
    }

    [[nodiscard]] VkDescriptorSet now() const;
  };
}
