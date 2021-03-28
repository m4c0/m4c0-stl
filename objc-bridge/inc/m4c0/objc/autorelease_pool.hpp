
#pragma once

#include "m4c0/objc/casts.hpp"

namespace m4c0::objc {
  class autorelease_pool {
    id m_ar;

    static auto objc_new() {
      auto * ar_cls = objc_getClass("NSAutoreleasePool");
      return objc_msg_send<id>(ar_cls, "new");
    }

  public:
    autorelease_pool() : m_ar(objc_new()) {
    }
    ~autorelease_pool() {
      objc_msg_send<void>(m_ar, "drain");
    }

    autorelease_pool(autorelease_pool &&) = delete;
    autorelease_pool(const autorelease_pool &) = delete;
    autorelease_pool & operator=(autorelease_pool &&) = delete;
    autorelease_pool & operator=(const autorelease_pool &) = delete;
  };
}
