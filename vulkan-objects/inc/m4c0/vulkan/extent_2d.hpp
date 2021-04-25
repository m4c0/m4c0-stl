#pragma once

namespace m4c0::vulkan {
  class extent_2d {
    unsigned m_width {};
    unsigned m_height {};

  public:
    constexpr extent_2d() = default;
    constexpr extent_2d(unsigned w, unsigned h) : m_width(w), m_height(h) {
    }
    constexpr extent_2d(float w, float h) : m_width(static_cast<unsigned>(w)), m_height(static_cast<unsigned>(h)) {
    }

    [[nodiscard]] constexpr float aspect_ratio() const noexcept {
      return static_cast<float>(m_width) / static_cast<float>(m_height);
    }

    [[nodiscard]] constexpr auto height() const noexcept {
      return m_height;
    }
    [[nodiscard]] constexpr auto width() const noexcept {
      return m_width;
    }

    constexpr void set(unsigned w, unsigned h) noexcept {
      m_width = w;
      m_height = h;
    }
  };
}
