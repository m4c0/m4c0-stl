#pragma once

#include "m4c0/native_handles.hpp"

#include <memory>

namespace m4c0::casein {
  class handler {
  public:
  };
  std::unique_ptr<handler> main(const native_handles * nh);
}
