#pragma once

namespace m4c0::vulkan {
  class command_buffer;

  class command_buffer_guard {
    const command_buffer * m_cmd_buf {};

    explicit constexpr command_buffer_guard(const command_buffer * cmd_buf) : m_cmd_buf(cmd_buf) {
    }

  public:
    constexpr command_buffer_guard() = default;
    ~command_buffer_guard();

    command_buffer_guard(const command_buffer_guard &) = delete;
    command_buffer_guard(command_buffer_guard &&) = delete;
    command_buffer_guard & operator=(const command_buffer_guard &) = delete;
    command_buffer_guard & operator=(command_buffer_guard &&) = delete;

    [[nodiscard]] constexpr const command_buffer * pointer() const noexcept {
      return m_cmd_buf;
    }

    [[nodiscard]] static command_buffer_guard begin_one_time_submit(const command_buffer * cb);
    //[[nodiscard]] static command_buffer_guard begin_render_pass_continue(VkCommandBuffer cb);
  };
}
