#pragma once

#include <vector>

using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::vulkan {
  class command_pool;
}

namespace m4c0::vulkan::actions {
  class allocate_command_buffers {
    const command_pool * m_pool;
    unsigned m_size;

  public:
    constexpr allocate_command_buffers() = default;

    [[nodiscard]] allocate_command_buffers & with_command_pool(const command_pool * cp) noexcept {
      m_pool = cp;
      return *this;
    }
    [[nodiscard]] allocate_command_buffers & with_size(unsigned s) noexcept {
      m_size = s;
      return *this;
    }

    [[nodiscard]] std::vector<VkCommandBuffer> as_primary() const;
    [[nodiscard]] std::vector<VkCommandBuffer> as_secondary() const;
  };
}
