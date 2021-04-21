#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan {
  class buffer;
}
namespace m4c0::vulkan::cmd {
  class bind_index_buffer : base_command {
    const buffer * m_buffer {};
    unsigned m_index {};

  public:
    using base_command::base_command;
    explicit constexpr bind_index_buffer(const base_command & o) : base_command(o) {
    }

    [[nodiscard]] constexpr bind_index_buffer & with_buffer(const buffer * p) noexcept {
      m_buffer = p;
      return *this;
    }
    [[nodiscard]] constexpr bind_index_buffer & with_index(unsigned i) noexcept {
      m_index = i;
      return *this;
    }

    void now() const;
  };
}
