#pragma once

#include "m4c0/vulkan/bind_buffer_memory.hpp"

namespace m4c0::vulkan::tools {
  /// \brief Allows a RAII-like interface to bind an buffer to device memory
  struct buffer_memory_bind {
    buffer_memory_bind() = default;
    buffer_memory_bind(const m4c0::vulkan::buffer * i, const m4c0::vulkan::device_memory * m, unsigned offset = 0) {
      m4c0::vulkan::actions::bind_buffer_memory().with_device_memory(m).with_buffer(i).with_offset(offset).now();
    }
  };
}
