#pragma once

#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/image_memory_bind.hpp"
#include "m4c0/vulkan/image_view.hpp"
#include "m4c0/vulkan/logical_device.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"

namespace m4c0::vulkan::tools {
  class local_image {
    image m_image {};
    device_memory m_memory {};
    image_memory_bind m_bind;
    image_view m_image_view {};

  public:
    constexpr local_image() = default;
    local_image(const logical_device * d, unsigned w, unsigned h)
      : m_image { image::create_rgba_with_extent(w, h) }
      , m_memory { device_memory::create_local_memory(d->physical_device(), m_image.memory_requirements()) }
      , m_bind { &m_image, &m_memory }
      , m_image_view { m4c0::vulkan::image_view::create_rgba_for_image(&m_image) } {
    }

    [[nodiscard]] constexpr auto * image() const noexcept {
      return &m_image;
    }
    [[nodiscard]] constexpr auto * image_view() const noexcept {
      return &m_image_view;
    }
  };
}
