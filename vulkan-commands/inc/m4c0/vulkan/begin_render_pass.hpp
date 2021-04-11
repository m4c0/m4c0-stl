#pragma once

#include "m4c0/vulkan/base_command.hpp"

#include <cstdint>

namespace m4c0::vulkan {
  class framebuffer;
  class render_pass;
}

namespace m4c0::vulkan::cmd {
  class begin_render_pass : base_command {
    float m_clear_color_r = 0;
    float m_clear_color_g = 0;
    float m_clear_color_b = 0;
    float m_clear_color_a = 1;
    float m_width;
    float m_height;
    float m_clear_depth = 1.0F;
    std::uint32_t m_clear_stencil = 0.0F;
    const framebuffer * m_framebuffer;
    const render_pass * m_render_pass;

  public:
    using base_command::base_command;
    void now() const;

    [[nodiscard]] begin_render_pass & with_extent(float w, float h) noexcept {
      m_width = w;
      m_height = h;
      return *this;
    }
    [[nodiscard]] begin_render_pass & with_clear_color(float r, float g, float b, float a) noexcept {
      m_clear_color_r = r;
      m_clear_color_g = g;
      m_clear_color_b = b;
      m_clear_color_a = a;
      return *this;
    }
    [[nodiscard]] begin_render_pass & with_clear_depth(float d) noexcept {
      m_clear_depth = d;
      return *this;
    }
    [[nodiscard]] begin_render_pass & with_clear_stencil(std::uint32_t s) noexcept {
      m_clear_stencil = s;
      return *this;
    }
    [[nodiscard]] begin_render_pass & with_framebuffer(const framebuffer * fb) noexcept {
      m_framebuffer = fb;
      return *this;
    }
    [[nodiscard]] begin_render_pass & with_render_pass(const render_pass * rp) noexcept {
      m_render_pass = rp;
      return *this;
    }
  };
}
