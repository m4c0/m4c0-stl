#pragma once

namespace m4c0::objc {
  class autorelease_pool {
    void * m_ar;

  public:
    autorelease_pool();
    ~autorelease_pool();

    autorelease_pool(autorelease_pool &&) = delete;
    autorelease_pool(const autorelease_pool &) = delete;
    autorelease_pool & operator=(autorelease_pool &&) = delete;
    autorelease_pool & operator=(const autorelease_pool &) = delete;
  };
}
