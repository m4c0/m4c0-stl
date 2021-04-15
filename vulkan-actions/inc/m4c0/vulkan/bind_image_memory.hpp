#pragma once

namespace m4c0::vulkan {
  class device_memory;
  class image;
}
namespace m4c0::vulkan::actions {
  class bind_image_memory {
    const image * m_image;
    const device_memory * m_memory;
    unsigned m_offset;

  public:
    [[nodiscard]] constexpr bind_image_memory & with_image(const image * i) noexcept {
      m_image = i;
      return *this;
    }
    [[nodiscard]] constexpr bind_image_memory & with_device_memory(const device_memory * m) noexcept {
      m_memory = m;
      return *this;
    }
    [[nodiscard]] constexpr bind_image_memory & with_offset(unsigned o) noexcept {
      m_offset = o;
      return *this;
    }
    void now() const;
  };
}
