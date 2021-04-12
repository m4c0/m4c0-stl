#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan {
  class pipeline_layout;
}

namespace m4c0::vulkan::cmd {
  class push_constants : base_command {
    const pipeline_layout * m_pipeline_layout;
    unsigned m_offset {};
    unsigned m_length;
    const void * m_data;

  public:
    using base_command::base_command;

    [[nodiscard]] constexpr push_constants & with_pipeline_layout(const pipeline_layout * p) noexcept {
      m_pipeline_layout = p;
      return *this;
    }

    [[nodiscard]] constexpr push_constants & with_offset(unsigned offset) noexcept {
      m_offset = offset;
      return *this;
    }

    template<typename Tp>
    [[nodiscard]] constexpr push_constants & with_data_from(const Tp * ptr) noexcept {
      m_data = ptr;
      m_length = sizeof(Tp);
      return *this;
    }

    void to_vertex_stage() const;
  };
}
