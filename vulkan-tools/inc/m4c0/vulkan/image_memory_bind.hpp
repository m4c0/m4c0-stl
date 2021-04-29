#pragma once

#include "m4c0/vulkan/bind_image_memory.hpp"

namespace m4c0::vulkan::tools {
  /// \brief Allows a RAII-like interface to bind an image to device memory
  struct image_memory_bind {
    image_memory_bind() = default;
    image_memory_bind(const m4c0::vulkan::image * i, const m4c0::vulkan::device_memory * m, unsigned offset = 0) {
      m4c0::vulkan::actions::bind_image_memory().with_device_memory(m).with_image(i).with_offset(offset).now();
    }
  };
}
