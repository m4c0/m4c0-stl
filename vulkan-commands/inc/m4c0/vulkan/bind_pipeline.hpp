#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan {
  class pipeline;
}
namespace m4c0::vulkan::cmd {
  class bind_pipeline : base_command {
    const pipeline * m_pipeline;

  public:
    using base_command::base_command;

    [[nodiscard]] constexpr bind_pipeline & with_pipeline(const pipeline * p) noexcept {
      m_pipeline = p;
      return *this;
    }

    void now() const;
  };
}
