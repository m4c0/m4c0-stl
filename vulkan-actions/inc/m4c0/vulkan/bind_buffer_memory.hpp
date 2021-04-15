#pragma once

namespace m4c0::vulkan {
  class buffer;
  class device_memory;
}
namespace m4c0::vulkan::actions {
  class bind_buffer_memory {
    const buffer * m_buffer;
    const device_memory * m_memory;
    unsigned m_offset;

  public:
    [[nodiscard]] constexpr bind_buffer_memory & with_buffer(const buffer * i) noexcept {
      m_buffer = i;
      return *this;
    }
    [[nodiscard]] constexpr bind_buffer_memory & with_device_memory(const device_memory * m) noexcept {
      m_memory = m;
      return *this;
    }
    [[nodiscard]] constexpr bind_buffer_memory & with_offset(unsigned o) noexcept {
      m_offset = o;
      return *this;
    }
    void now() const;
  };
}
