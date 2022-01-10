#pragma once

#include <utility>

namespace m4c0::containers {
  // constexpr variant of STL's
  template<typename Tp>
  class unique_ptr {
    Tp * m_ptr {};

  public:
    constexpr unique_ptr() noexcept = default;
    constexpr explicit unique_ptr(Tp * p) noexcept : m_ptr { p } {
    }
    constexpr ~unique_ptr() noexcept {
      delete m_ptr;
    }

    unique_ptr(const unique_ptr &) = delete;
    unique_ptr & operator=(const unique_ptr &) = delete;

    constexpr unique_ptr(unique_ptr && o) noexcept : m_ptr { o.m_ptr } {
      o.m_ptr = nullptr;
    }
    constexpr unique_ptr & operator=(unique_ptr && o) noexcept {
      delete m_ptr;
      m_ptr = o.m_ptr;
      o.m_ptr = nullptr;
      return *this;
    }

    [[nodiscard]] constexpr explicit operator bool() const noexcept {
      return m_ptr != nullptr;
    }

    [[nodiscard]] constexpr Tp & operator*() noexcept {
      return *m_ptr;
    }
    [[nodiscard]] constexpr const Tp & operator*() const noexcept {
      return *m_ptr;
    }

    template<typename... Args>
    [[nodiscard]] constexpr static unique_ptr<Tp> make(Args &&... args) noexcept {
      return unique_ptr<Tp>(new Tp { std::forward<Args>(args)... });
    }
  };
}
