#pragma once

#include "m4c0/assets/stb_image.hpp"
#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/buffer_memory_bind.hpp"
#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/logical_device.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"

namespace m4c0::vulkan::tools {
  class host_staged_image_buffer {
    buffer m_buffer;
    device_memory m_memory;
    buffer_memory_bind m_bind;
    unsigned m_width;
    unsigned m_height;

  public:
    host_staged_image_buffer(const logical_device * d, const assets::typed_stb_image<> & res)
      : m_buffer(buffer::create_transfer_source_with_size(res.data_length()))
      , m_memory(device_memory::create_host_memory(d->physical_device(), m_buffer.memory_requirements()))
      , m_bind(&m_buffer, &m_memory)
      , m_width(res.width())
      , m_height(res.height()) {
      auto m = m_memory.map_all();
      auto span = res.span();
      std::copy(span.begin(), span.end(), m.pointer<uint32_t>());
    }

    [[nodiscard]] constexpr auto width() const noexcept {
      return m_width;
    }
    [[nodiscard]] constexpr auto height() const noexcept {
      return m_height;
    }
    [[nodiscard]] constexpr auto * buffer() const noexcept {
      return &m_buffer;
    }
  };
}
