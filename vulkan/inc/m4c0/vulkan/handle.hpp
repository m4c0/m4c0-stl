#pragma once

namespace m4c0::vulkan::details {
  template<class Tp>
  class handle {
    Tp m_ptr;

  protected:
    explicit constexpr handle(Tp ptr) : m_ptr(ptr) {
    }

  public:
    ~handle() {
      reset();
    }

    handle(handle && o) noexcept : m_ptr(o.m_ptr) {
      o.m_ptr = nullptr;
    }
    handle & operator=(handle && o) noexcept {
      if (m_ptr != o.m_ptr) reset();
      m_ptr = o.m_ptr;
      o.m_ptr = nullptr;
    }

    handle(const handle &) = delete;
    handle & operator=(const handle &) = delete;

    [[nodiscard]] constexpr auto pointer() const noexcept {
      return m_ptr;
    }

    void reset();
  };
}
