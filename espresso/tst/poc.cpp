#include "m4c0/espresso/common.hpp"
#include "m4c0/espresso/constant.hpp"
#include "m4c0/espresso/reader.hpp"
#include "m4c0/io/ce_reader.hpp"

#include <stdexcept>

namespace m4c0::espresso {

  struct cls_header {
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    constant::pool cpool;
  };

  static constexpr cls_header read_header(m4c0::io::reader * r) {
    constexpr const auto class_magic_number = 0xCAFEBABE;
    constexpr const auto min_version = 45.0;
    constexpr const auto max_version = 55.0;

    cls_header res {};
    res.magic = unwrap(r->read_u32_be(), "Truncated magic number");
    if (res.magic != class_magic_number) throw std::runtime_error("Invalid magic number");

    res.minor_version = unwrap(r->read_u16_be(), "Truncated minor version");
    res.major_version = unwrap(r->read_u16_be(), "Truncated major version");
    if (res.major_version < min_version || res.major_version > max_version) {
      throw std::runtime_error("Unsupported version");
    }

    res.cpool = read_cpool(r);
    return res;
  }
}

/* Class generated with this Java code:
 *
 * package com.github.m4c0.espresso;
 *
 * public class Poc {
 *   public static void main(String a[]) {
 *   }
 * }
 */
static constexpr const auto cls_file =
    m4c0::io::ce_reader { "\xca\xfe\xba\xbe\x00\x00\x00\x37\x00\x0f\x0a\x00\x03\x00\x0c\x07\x00\x0d\x07"
                          "\x00\x0e\x01\x00\x06\x3c\x69\x6e\x69\x74\x3e\x01\x00\x03\x28\x29\x56\x01\x00"
                          "\x04\x43\x6f\x64\x65\x01\x00\x0f\x4c\x69\x6e\x65\x4e\x75\x6d\x62\x65\x72\x54"
                          "\x61\x62\x6c\x65\x01\x00\x04\x6d\x61\x69\x6e\x01\x00\x16\x28\x5b\x4c\x6a\x61"
                          "\x76\x61\x2f\x6c\x61\x6e\x67\x2f\x53\x74\x72\x69\x6e\x67\x3b\x29\x56\x01\x00"
                          "\x0a\x53\x6f\x75\x72\x63\x65\x46\x69\x6c\x65\x01\x00\x08\x50\x6f\x63\x2e\x6a"
                          "\x61\x76\x61\x0c\x00\x04\x00\x05\x01\x00\x1c\x63\x6f\x6d\x2f\x67\x69\x74\x68"
                          "\x75\x62\x2f\x6d\x34\x63\x30\x2f\x65\x73\x70\x72\x65\x73\x73\x6f\x2f\x50\x6f"
                          "\x63\x01\x00\x10\x6a\x61\x76\x61\x2f\x6c\x61\x6e\x67\x2f\x4f\x62\x6a\x65\x63"
                          "\x74\x00\x21\x00\x02\x00\x03\x00\x00\x00\x00\x00\x02\x00\x01\x00\x04\x00\x05"
                          "\x00\x01\x00\x06\x00\x00\x00\x1d\x00\x01\x00\x01\x00\x00\x00\x05\x2a\xb7\x00"
                          "\x01\xb1\x00\x00\x00\x01\x00\x07\x00\x00\x00\x06\x00\x01\x00\x00\x00\x03\x00"
                          "\x09\x00\x08\x00\x09\x00\x01\x00\x06\x00\x00\x00\x19\x00\x00\x00\x01\x00\x00"
                          "\x00\x01\xb1\x00\x00\x00\x01\x00\x07\x00\x00\x00\x06\x00\x01\x00\x00\x00\x05"
                          "\x00\x01\x00\x0a\x00\x00\x00\x02\x00\x0b" };

using namespace m4c0::espresso;

static constexpr auto run(auto fn) {
  auto c = cls_file;
  return fn(&c);
}
static_assert((*run(read_header).cpool).size() == 14); // NOLINT

int main() {
}
