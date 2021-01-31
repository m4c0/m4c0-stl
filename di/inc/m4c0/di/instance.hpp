#pragma once

#include <memory>

namespace m4c0::di {
  class instance {
    using deleter = void (*)(void *);

    void * m_ptr {};
    deleter m_del {};

  public:
    instance() = default;
    explicit instance(void * p, deleter d) : m_ptr(p), m_del(d) {
    }
    template<class Tp, class Deleter>
    explicit instance(std::unique_ptr<Tp, Deleter> && p)
      : instance(p.release(), [](void * ptr) {
        Deleter()(static_cast<Tp *>(ptr));
      }) {
    }
    ~instance() {
      if (m_del != nullptr) m_del(m_ptr);
    }

    instance(instance && o) noexcept : m_ptr(o.m_ptr), m_del(o.m_del) {
      o.m_ptr = nullptr;
      o.m_del = nullptr;
    }
    instance & operator=(instance && o) noexcept {
      if (&o == this) return *this;
      if (m_del != nullptr) m_del(m_ptr);
      m_ptr = o.m_ptr;
      m_del = o.m_del;
      o.m_ptr = nullptr;
      o.m_del = nullptr;
      return *this;
    }
    instance(const instance & o) = delete;
    instance & operator=(const instance & o) = delete;

    [[nodiscard]] void * get() const {
      return m_ptr;
    }
  };
}
