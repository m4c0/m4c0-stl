#pragma once

#include "m4c0/vulkan/base_render_pass_command.hpp"
#include "m4c0/vulkan/extent_2d.hpp"

#include <cstdint>

namespace m4c0::vulkan::cmd {
  class begin_render_pass : public base_render_pass_command<begin_render_pass> {
    float m_clear_color_r = 0;
    float m_clear_color_g = 0;
    float m_clear_color_b = 0;
    float m_clear_color_a = 1;
    float m_width;
    float m_height;
    float m_clear_depth = 1.0F;
    std::uint32_t m_clear_stencil = 0.0F;

  public:
    using base_render_pass_command::base_render_pass_command;
    void now() const;

    [[nodiscard]] begin_render_pass & with_extent(float w, float h) noexcept {
      m_width = w;
      m_height = h;
      return *this;
    }
    [[nodiscard]] begin_render_pass & with_extent(extent_2d e) noexcept {
      return with_extent(e.width(), e.height());
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
  };
}
