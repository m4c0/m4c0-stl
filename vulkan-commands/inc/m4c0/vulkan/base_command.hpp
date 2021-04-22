#pragma once

using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::vulkan::cmd {
  class base_command {
    VkCommandBuffer m_cmd_buf;

    friend class execute_commands;

  protected:
    [[nodiscard]] constexpr VkCommandBuffer pointer() const noexcept {
      return m_cmd_buf;
    }

  public:
    explicit constexpr base_command(VkCommandBuffer cb) : m_cmd_buf(cb) {
    }
  };
}
