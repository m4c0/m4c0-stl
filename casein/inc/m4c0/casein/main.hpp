#pragma once

#include "m4c0/native_handles.hpp"

#include <memory>

namespace m4c0::casein {
  class handler {
  public:
    handler() = default;
    virtual ~handler() = default;

    handler(handler &&) = delete;
    handler(const handler &) = delete;
    handler & operator=(handler &&) = delete;
    handler & operator=(const handler &) = delete;
  };
  std::unique_ptr<handler> main(const native_handles * nh);
}
