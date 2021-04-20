#pragma once

#include <span>

using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::vulkan {
  class command_pool;
}

namespace m4c0::vulkan::actions {
  class allocate_command_buffers {
    const command_pool * m_pool {};

  public:
    constexpr allocate_command_buffers() = default;

    [[nodiscard]] allocate_command_buffers & with_command_pool(const command_pool * cp) noexcept {
      m_pool = cp;
      return *this;
    }

    using span_t = std::span<VkCommandBuffer>;
    void as_primary_into(span_t s) const;
    void as_secondary_into(span_t s) const;
  };
}
