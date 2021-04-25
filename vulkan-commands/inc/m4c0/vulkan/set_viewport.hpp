#pragma once

#include "m4c0/vulkan/base_command.hpp"
#include "m4c0/vulkan/extent_2d.hpp"

#include <span>

namespace m4c0::vulkan {
  class buffer;
}
namespace m4c0::vulkan::cmd {
  class set_viewport : base_command {
    float m_width {};
    float m_height {};

  public:
    using base_command::base_command;
    explicit constexpr set_viewport(const base_command & o) : base_command(o) {
    }

    [[nodiscard]] constexpr set_viewport & with_size(float w, float h) noexcept {
      m_width = w;
      m_height = h;
      return *this;
    }
    [[nodiscard]] constexpr set_viewport & with_size(extent_2d e) noexcept {
      return with_size(e.width(), e.height());
    }

    void now() const;
  };
}
