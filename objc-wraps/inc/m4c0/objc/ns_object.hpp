#pragma once

namespace m4c0::objc {
  using cg_float = double; // except watchos

  class ns_object {
    void * m_object;

  public:
    // [[cls alloc] init]
    explicit ns_object(const char * cls_name);
    // [obj retain]
    explicit ns_object(void * obj);
    // [cls method] - ex: [NSApp sharedApp]
    ns_object(const char * cls_name, const char * method);
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
