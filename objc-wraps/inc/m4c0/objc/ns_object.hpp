#pragma once

#include <TargetConditionals.h>
#include <cstddef>

namespace m4c0::objc {
  using cg_float = double; // except watchos

  class ns_object {
    void * m_object {};

  protected:
    template<class Tp>
    Tp get(const char * getter) const;
    template<class Tp>
    void set(const char * setter, const Tp & o) const;
    void send(const char * msg) const;

  public:
    explicit constexpr ns_object(std::nullptr_t /*unused*/) {
    }
    // [[cls alloc] init]
    explicit ns_object(const char * cls_name);
    // [obj retain]
    explicit ns_object(void * obj);
    // [cls method] - ex: [NSApp sharedApp]
    ns_object(const char * cls_name, const char * method, bool retain);
    // [obj release]
    ~ns_object();

    ns_object(const ns_object & o);
    ns_object(ns_object && o) = delete;
    ns_object & operator=(const ns_object & o);
    ns_object & operator=(ns_object && o) = delete;

    [[nodiscard]] constexpr explicit operator bool() const noexcept {
      return m_object != nullptr;
    }

    [[nodiscard]] constexpr auto * self() const noexcept {
      return m_object;
    }
  };
}
