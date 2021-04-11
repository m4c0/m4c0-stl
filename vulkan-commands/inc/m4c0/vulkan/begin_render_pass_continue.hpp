#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan {
  class framebuffer;
  class render_pass;
}
namespace m4c0::vulkan::cmd {
  class begin_render_pass_continue : base_command {
    const framebuffer * m_framebuffer {};
    const render_pass * m_render_pass {};

  public:
    using base_command::base_command;

    [[nodiscard]] begin_render_pass_continue & with_framebuffer(const framebuffer * fb) {
      m_framebuffer = fb;
      return *this;
    }
    [[nodiscard]] begin_render_pass_continue & with_render_pass(const render_pass * rp) {
      m_render_pass = rp;
      return *this;
    }

    void now() const;
  };
}
