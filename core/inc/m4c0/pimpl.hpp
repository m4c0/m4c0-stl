#pragma once

#include <memory>
#include <utility>

namespace m4c0 {
  template<typename Tp>
  class pimpl {
    Tp * m_ptr {};
    void (*m_deleter)(Tp *) {};

  public:
    constexpr pimpl() = default;
    ~pimpl() {
      reset();
      if (m_deleter) m_deleter(m_ptr);
    }

    pimpl(pimpl<Tp> && o) noexcept : m_ptr(o.m_ptr), m_deleter(o.m_deleter) {
      o.m_ptr = nullptr;
      o.m_deleter = nullptr;
    }
    pimpl & operator=(pimpl<Tp> && o) noexcept {
      if (&o == this) return *this;
      reset();
      m_ptr = o.m_ptr;
      m_deleter = o.m_deleter;
      o.m_ptr = nullptr;
      o.m_deleter = nullptr;
      return *this;
    }

    pimpl(const pimpl<Tp> &) = delete;
    pimpl operator=(const pimpl<Tp> &) = delete;

    [[nodiscard]] constexpr Tp * operator->() const noexcept {
      return m_ptr;
    }
    [[nodiscard]] constexpr Tp & operator*() const noexcept {
      return *m_ptr;
    }

    [[nodiscard]] constexpr explicit operator bool() const noexcept {
      return m_ptr != nullptr;
    }

    [[nodiscard]] constexpr Tp * get() const noexcept {
      return m_ptr;
    }

    void reset() noexcept {
      if (m_deleter) m_deleter(m_ptr);
      m_deleter = nullptr;
      m_ptr = nullptr;
    }

    template<typename... Args>
    void make_new(Args &&... args) {
      m_ptr = new Tp(std::forward<Args>(args)...); // NOLINT
      m_deleter = [](Tp * p) {
        std::default_delete<Tp>()(p);
      };
    }
  };
}
