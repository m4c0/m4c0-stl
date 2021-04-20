#pragma once

#include "m4c0/vulkan/semaphore.hpp"

namespace m4c0::vulkan::tools {
  template<class Id>
  struct typed_semaphore : public semaphore {};
}
