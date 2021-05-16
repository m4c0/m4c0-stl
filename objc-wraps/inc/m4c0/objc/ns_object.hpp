#pragma once

namespace m4c0::objc {
  class ns_object {
    void * m_class;
    void * m_object;

  public:
    // [[cls alloc] init]
    explicit ns_object(const char * cls_name);
    // [cls method] - ex: [NSApp sharedApp]
    ns_object(const char * cls_name, const char * method);
    // [obj retain]
    ns_object(const char * cls_name, void * obj);
    // [obj release]
    ~ns_object();

    ns_object(const ns_object & o);
    ns_object(ns_object && o) = delete;
    ns_object & operator=(const ns_object & o);
    ns_object & operator=(ns_object && o) = delete;

    [[nodiscard]] constexpr auto * self() const noexcept {
      return m_object;
    }
  };
}
