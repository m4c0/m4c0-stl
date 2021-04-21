#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan {
  class framebuffer;
  class render_pass;
}

namespace m4c0::vulkan::cmd {
  /// Convenience to simplify render pass command creation. This reduces the boilerplate to pass both framebuffer and
  /// render_pass instances.
  template<class Tp>
  class base_render_pass_command;

  template<>
  class base_render_pass_command<void> : public base_command {
    const framebuffer * m_framebuffer {};
    const render_pass * m_render_pass {};

  protected:
    [[nodiscard]] constexpr auto * framebuffer() const noexcept {
      return m_framebuffer;
    }
    [[nodiscard]] constexpr auto * render_pass() const noexcept {
      return m_render_pass;
    }

  public:
    using base_command::base_command;
    explicit base_render_pass_command(const base_command & o) : base_command(o) {
    }

    [[nodiscard]] auto & with_framebuffer(const vulkan::framebuffer * fb) noexcept {
      m_framebuffer = fb;
      return *this;
    }
    [[nodiscard]] auto & with_render_pass(const vulkan::render_pass * rp) noexcept {
      m_render_pass = rp;
      return *this;
    }
  };

  template<class Tp>
  struct base_render_pass_command : public base_render_pass_command<void> {
    using base_render_pass_command<void>::base_render_pass_command;

    explicit base_render_pass_command(const base_render_pass_command<void> & o) : base_render_pass_command<void>(o) {
    }
    explicit base_render_pass_command(const base_command & o) : base_render_pass_command<void>(o) {
    }

    [[nodiscard]] Tp & with_framebuffer(const vulkan::framebuffer * fb) noexcept {
      return static_cast<Tp &>(base_render_pass_command<void>::with_framebuffer(fb));
    }
    [[nodiscard]] Tp & with_render_pass(const vulkan::render_pass * rp) noexcept {
      return static_cast<Tp &>(base_render_pass_command<void>::with_render_pass(rp));
    }
  };
}
