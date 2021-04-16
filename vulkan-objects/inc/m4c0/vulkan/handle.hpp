#pragma once

struct VkDevice_T;
struct VkInstance_T;

namespace m4c0::vulkan::details {
  template<class Tp>
  struct ptr_type_traits {
    using handle_t = Tp *;
  };
  template<class Tp>
  struct u64_type_traits {
    using handle_t = unsigned long long; // NOLINT(google-runtime-int)
  };

  template<class Tp, bool IsPtr = true>
  struct type_traits : ptr_type_traits<Tp> {};
  template<>
  struct type_traits<VkDevice_T> : ptr_type_traits<VkDevice_T> {};
  template<>
  struct type_traits<VkInstance_T> : ptr_type_traits<VkInstance_T> {};
  template<class Tp>
  struct type_traits<Tp, sizeof(void *) == 4> : u64_type_traits<Tp> {};

  template<class Tp>
  struct base_handle {
    using type_t = typename type_traits<Tp>::handle_t;

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
  class handle : public base_handle<Tp> {
  protected:
    using base_handle<Tp>::base_handle;
  };

  template<class Tp>
  class nd_handle : public base_handle<Tp> {
  protected:
    using base_handle<Tp>::base_handle;
  };

  template<class Tp>
  using pointer_t = typename nd_handle<Tp>::type_t;
}
