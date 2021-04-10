#pragma once

using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::vulkan {
  class base_command {
    VkCommandBuffer m_cmd_buf;

  protected:
    explicit constexpr base_command(VkCommandBuffer cb) : m_cmd_buf(cb) {
    }

    [[nodiscard]] constexpr VkCommandBuffer pointer() const noexcept {
      return m_cmd_buf;
    }
  };
}
