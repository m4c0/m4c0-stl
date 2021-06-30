#pragma once

#include "m4c0/native_handles.hpp"

#include <cstdint>
#include <span>

namespace m4c0::assets {
  class simple_asset;

  class stb_image {
    int m_width;
    int m_height;
    void * m_data;

  public:
    explicit stb_image(const simple_asset * r);
    ~stb_image();

    stb_image(const stb_image &) = delete;
    stb_image(stb_image &&) = delete;
    stb_image & operator=(const stb_image &) = delete;
    stb_image & operator=(stb_image &&) = delete;

    [[nodiscard]] constexpr auto width() const noexcept {
      return m_width;
    }
    [[nodiscard]] constexpr auto height() const noexcept {
      return m_height;
    }
    [[nodiscard]] constexpr const auto * data() const noexcept {
      return m_data;
    }

    [[nodiscard]] static stb_image load_from_asset(const native_handles * nptr, const char * name, const char * ext);
  };

  template<class Tp = std::uint32_t>
  class typed_stb_image {
    stb_image m_img;

    typed_stb_image(const native_handles * nptr, const char * name, const char * ext)
      : m_img(stb_image::load_from_asset(nptr, name, ext)) {
    }

  public:
    [[nodiscard]] constexpr auto width() const noexcept {
      return m_img.width();
    }
    [[nodiscard]] constexpr auto height() const noexcept {
      return m_img.height();
    }

    [[nodiscard]] constexpr auto data_length() const noexcept {
      constexpr const int bytes_per_pixel = sizeof(Tp);
      return m_img.width() * m_img.height() * bytes_per_pixel;
    }

    [[nodiscard]] constexpr auto span() const noexcept {
      return std::span<const Tp>(static_cast<const Tp *>(m_img.data()), m_img.width() * m_img.height());
    }

    [[nodiscard]] static typed_stb_image load_from_asset(
        const native_handles * nptr,
        const char * name,
        const char * ext) {
      return { nptr, name, ext };
    }
  };
}
