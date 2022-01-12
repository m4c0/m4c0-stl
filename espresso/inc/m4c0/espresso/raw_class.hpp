#pragma once

#include "m4c0/containers/unique_array.hpp"
#include "m4c0/espresso/constant.hpp"

namespace m4c0::espresso::raw {
  struct attribute {
    uint16_t name {};
    containers::unique_array<uint8_t> info {}; // up to u32
  };
  struct member {
    uint16_t flags {};
    uint16_t name {};
    uint16_t descriptor {};
    containers::unique_array<attribute> attributes {};
  };
  struct cls_header {
    uint32_t magic {};
    uint16_t minor_version {};
    uint16_t major_version {};
    constant::pool cpool {};
    uint16_t flags {};
    uint16_t this_class {};
    uint16_t super_class {};
    containers::unique_array<uint16_t> ifaces {};
    containers::unique_array<member> fields {};
    containers::unique_array<member> methods {};
    containers::unique_array<attribute> attributes {};
  };
}
