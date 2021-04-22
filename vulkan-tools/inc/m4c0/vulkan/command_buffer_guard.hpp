#pragma once

#include "m4c0/vulkan/end_command_buffer.hpp"

namespace m4c0::vulkan::tools {
  class command_buffer_guard {
    VkCommandBuffer m_cmd_buf;

  public:
    explicit constexpr command_buffer_guard(VkCommandBuffer cb) : m_cmd_buf(cb) {
    }
    ~command_buffer_guard() {
      cmd::end_command_buffer(m_cmd_buf).now();
    }

    command_buffer_guard(command_buffer_guard &&) = delete;
    command_buffer_guard(const command_buffer_guard &) = delete;
    command_buffer_guard & operator=(command_buffer_guard &&) = delete;
    command_buffer_guard & operator=(const command_buffer_guard &) = delete;

    [[nodiscard]] constexpr auto command_buffer() const noexcept {
      return m_cmd_buf;
    }
  };
}
