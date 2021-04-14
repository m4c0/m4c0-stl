#pragma once

#include <exception>

namespace m4c0::vulkan {
  class out_of_date_error : std::exception {};
}
