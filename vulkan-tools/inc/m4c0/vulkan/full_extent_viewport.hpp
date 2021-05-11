#pragma once

#include "m4c0/vulkan/extent_2d.hpp"
#include "m4c0/vulkan/set_scissor.hpp"
#include "m4c0/vulkan/set_viewport.hpp"

namespace m4c0::vulkan::tools {
  class full_extent_viewport {
    extent_2d m_extent;

  public:
    [[nodiscard]] constexpr auto extent() const noexcept {
      return m_extent;
    }
    [[nodiscard]] constexpr auto & extent() noexcept {
      return m_extent;
    }

    void build_command_buffer(VkCommandBuffer cmd_buf) const {
      m4c0::vulkan::cmd::set_scissor(cmd_buf).with_size(m_extent).now();
      m4c0::vulkan::cmd::set_viewport(cmd_buf).with_size(m_extent).now();
    }
  };
}
