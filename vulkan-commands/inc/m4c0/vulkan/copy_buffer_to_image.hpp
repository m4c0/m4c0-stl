#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan {
  class buffer;
  class image;
}
namespace m4c0::vulkan::cmd {
  class copy_buffer_to_image : base_command {
    const buffer * m_source;
    unsigned m_source_offset;
    const image * m_target;
    unsigned m_target_width;
    unsigned m_target_height;

  public:
    using base_command::base_command;

    [[nodiscard]] constexpr copy_buffer_to_image & with_source_buffer(const buffer * src) noexcept {
      m_source = src;
      return *this;
    }
    [[nodiscard]] constexpr copy_buffer_to_image & with_source_offset(unsigned offset) noexcept {
      m_source_offset = offset;
      return *this;
    }
    [[nodiscard]] constexpr copy_buffer_to_image & with_target_image(const image * img) noexcept {
      m_target = img;
      return *this;
    }
    [[nodiscard]] constexpr copy_buffer_to_image & with_target_extent(unsigned w, unsigned h) noexcept {
      m_target_width = w;
      m_target_height = h;
      return *this;
    }

    void now() const;
  };
}
