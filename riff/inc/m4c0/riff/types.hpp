#pragma once

#include <cstdint>

namespace m4c0::riff {
  using fourcc_t = std::uint32_t;
  struct header {
    fourcc_t fourcc;
    std::uint32_t length;
  };
}
