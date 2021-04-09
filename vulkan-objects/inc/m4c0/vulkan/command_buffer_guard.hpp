#pragma once

namespace m4c0::vulkan {
  class command_buffer;
  class framebuffer;
  class render_pass;

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

    class render_pass_continue {
      const command_buffer * m_cmd_buf;
      const framebuffer * m_framebuffer {};
      const render_pass * m_render_pass {};

    public:
      explicit constexpr render_pass_continue(const command_buffer * cb) : m_cmd_buf(cb) {
      }
      [[nodiscard]] render_pass_continue & with_framebuffer(const framebuffer * fb) {
        m_framebuffer = fb;
        return *this;
      }
      [[nodiscard]] render_pass_continue & with_render_pass(const render_pass * rp) {
        m_render_pass = rp;
        return *this;
      }
      [[nodiscard]] command_buffer_guard begin() const;
    };
  };
}
