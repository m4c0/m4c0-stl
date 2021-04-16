#pragma once

namespace m4c0::vulkan::details {
  template<class Tp>
  struct handle {
    using type_t = Tp;

  private:
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
      o.m_ptr = {};
    }
    handle & operator=(handle && o) noexcept {
      if (m_ptr && m_ptr != o.m_ptr) reset();
      m_ptr = o.m_ptr;
      o.m_ptr = {};
      return *this;
    }

    handle(const handle &) = delete;
    handle & operator=(const handle &) = delete;

    [[nodiscard]] constexpr type_t pointer() const noexcept {
      return m_ptr;
    }
  };

  template<class Tp, unsigned PtSize = sizeof(void *)>
  class nd_handle : public handle<Tp *> {
  protected:
    using handle<Tp *>::handle;
  };

  using ndh_t = unsigned long long;  // NOLINT(google-runtime-int)
  static_assert(sizeof(ndh_t) == 8); // NOLINT

  template<class Tp>
  class nd_handle<Tp, 4> : public handle<ndh_t> {
  protected:
    using handle<ndh_t>::handle;
  };

  template<class Tp>
  using pointer_t = typename nd_handle<Tp>::type_t;
}
