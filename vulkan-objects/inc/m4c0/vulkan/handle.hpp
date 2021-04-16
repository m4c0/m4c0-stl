#pragma once

namespace m4c0::vulkan::details {
  template<class Tp>
  struct base_handle {
    using type_t = Tp;

  private:
    type_t m_ptr;

    void reset();

  protected:
    explicit constexpr base_handle(type_t ptr) : m_ptr(ptr) {
    }

  public:
    ~base_handle() {
      if (m_ptr) reset();
    }

    constexpr base_handle() = default;
    base_handle(base_handle && o) noexcept : m_ptr(o.m_ptr) {
      o.m_ptr = {};
    }
    base_handle & operator=(base_handle && o) noexcept {
      if (m_ptr && m_ptr != o.m_ptr) reset();
      m_ptr = o.m_ptr;
      o.m_ptr = {};
      return *this;
    }

    base_handle(const base_handle &) = delete;
    base_handle & operator=(const base_handle &) = delete;

    [[nodiscard]] constexpr type_t pointer() const noexcept {
      return m_ptr;
    }
  };

  template<class Tp>
  class handle : public base_handle<Tp *> {
  protected:
    using base_handle<Tp *>::base_handle;
  };

  template<class Tp, unsigned PtSize = sizeof(void *)>
  class nd_handle : public base_handle<Tp *> {
  protected:
    using base_handle<Tp *>::base_handle;
  };

  using ndh_t = unsigned long long;  // NOLINT(google-runtime-int)
  static_assert(sizeof(ndh_t) == 8); // NOLINT

  template<class Tp>
  class nd_handle<Tp, 4> : public base_handle<ndh_t> {
  protected:
    using base_handle<ndh_t>::base_handle;
  };

  template<class Tp>
  using pointer_t = typename nd_handle<Tp>::type_t;
}
