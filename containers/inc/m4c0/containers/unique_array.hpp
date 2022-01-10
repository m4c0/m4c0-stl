#pragma once

#include <cassert>
#include <utility>

namespace m4c0::containers {
  // constexpr variant of STL's
  template<typename Tp>
  class unique_array {
    Tp * m_ptr {};
    size_t m_len {};

  public:
    constexpr unique_array() noexcept = default;
    constexpr explicit unique_array(size_t n) noexcept : m_ptr { new Tp[n] }, m_len { n } {
    }
    constexpr ~unique_array() noexcept {
      delete[] m_ptr;
    }

    unique_array(const unique_array &) = delete;
    unique_array & operator=(const unique_array &) = delete;

    constexpr unique_array(unique_array && o) noexcept : m_ptr { o.m_ptr }, m_len { o.m_len } {
      o.m_ptr = nullptr;
      o.m_len = 0;
    }
    constexpr unique_array & operator=(unique_array && o) noexcept {
      delete[] m_ptr;
      m_ptr = o.m_ptr;
      m_len = o.m_len;
      o.m_ptr = nullptr;
      o.m_len = 0;
      return *this;
    }

    [[nodiscard]] constexpr explicit operator bool() const noexcept {
      return m_ptr != nullptr;
    }

    [[nodiscard]] constexpr Tp & operator[](size_t idx) noexcept {
      assert(idx < m_len);
      return m_ptr[idx]; // NOLINT
    }
    [[nodiscard]] constexpr const Tp & operator[](size_t idx) const noexcept {
      assert(idx < m_len);
      return m_ptr[idx]; // NOLINT
    }

    [[nodiscard]] constexpr auto begin() noexcept {
      return m_ptr;
    }
    [[nodiscard]] constexpr auto end() noexcept {
      return m_ptr + m_len;
    }
    [[nodiscard]] constexpr auto begin() const noexcept {
      return m_ptr;
    }
    [[nodiscard]] constexpr auto end() const noexcept {
      return m_ptr + m_len;
    }
  };
}
