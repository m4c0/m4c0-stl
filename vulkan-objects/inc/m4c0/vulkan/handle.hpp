#pragma once

namespace m4c0::vulkan::details {
  template<class Tp>
  class handle {
    using type_t = Tp;

    type_t m_ptr;

    void reset();

  protected:
    explicit constexpr handle(type_t ptr) : m_ptr(ptr) {
    }

  public:
    ~handle() {
      if (m_ptr) reset();
    }

    constexpr handle() = default;
    handle(handle && o) noexcept : m_ptr(o.m_ptr) {
      o.m_ptr = nullptr;
    }
    handle & operator=(handle && o) noexcept {
      if (m_ptr && m_ptr != o.m_ptr) reset();
      m_ptr = o.m_ptr;
      o.m_ptr = nullptr;
      return *this;
    }

    handle(const handle &) = delete;
    handle & operator=(const handle &) = delete;

    [[nodiscard]] constexpr type_t pointer() const noexcept {
      return m_ptr;
    }
  };
}
