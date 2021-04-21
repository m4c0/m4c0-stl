#pragma once

#include "m4c0/vulkan/base_command.hpp"

#include <span>

namespace m4c0::vulkan {
  class buffer;
}
namespace m4c0::vulkan::cmd {
  class update_buffer : base_command {
    const buffer * m_buffer {};
    unsigned m_offset {};
    std::span<void *> m_data {};

  public:
    using base_command::base_command;
    explicit constexpr update_buffer(const base_command & o) : base_command(o) {
    }

    [[nodiscard]] constexpr update_buffer & with_buffer(const buffer * b) noexcept {
      m_buffer = b;
      return *this;
    }
    [[nodiscard]] constexpr update_buffer & with_offset(unsigned u) noexcept {
      m_offset = u;
      return *this;
    }
    [[nodiscard]] constexpr update_buffer & with_data(std::span<void *> d) noexcept {
      m_data = d;
      return *this;
    }

    void now() const;
  };
}
