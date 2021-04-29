#pragma once

#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/extent_2d.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/image_memory_bind.hpp"
#include "m4c0/vulkan/image_view.hpp"

namespace m4c0::fuji {
  class device_context;

  class depth_buffer {
    vulkan::image m_image;
    vulkan::device_memory m_memory;
    vulkan::tools::image_memory_bind m_bind;
    vulkan::image_view m_image_view;

  public:
    depth_buffer(const device_context * ld, vulkan::extent_2d re);

    [[nodiscard]] constexpr auto * image_view() const noexcept {
      return &m_image_view;
    }
  };
}
