#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan::cmd {
  class draw : base_command {
    unsigned m_vtx_count;
    unsigned m_vtx_first = 0;
    unsigned m_inst_count = 1;
    unsigned m_inst_first = 0;

  public:
    using base_command::base_command;

    [[nodiscard]] constexpr draw & with_vertex_count(unsigned v) noexcept {
      m_vtx_count = v;
      return *this;
    }
    [[nodiscard]] constexpr draw & with_first_vertex(unsigned v) noexcept {
      m_vtx_first = v;
      return *this;
    }
    [[nodiscard]] constexpr draw & with_instance_count(unsigned i) noexcept {
      m_inst_count = i;
      return *this;
    }
    [[nodiscard]] constexpr draw & with_first_instance(unsigned i) noexcept {
      m_inst_first = i;
      return *this;
    }

    void now() const;
  };
}
