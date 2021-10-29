#include "m4c0/espresso/base_parsing.hpp"
#include "m4c0/espresso/cpool.hpp"
#include "m4c0/espresso/magic.hpp"
#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/result.hpp"

#include <limits>

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
    m4c0::parser::input_t { "\xca\xfe\xba\xbe\x00\x00\x00\x37\x00\x0f\x0a\x00\x03\x00\x0c\x07\x00\x0d\x07"
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

namespace m4c0::espresso {
  struct iface {
    constexpr iface operator+(const constant::pool & /*r*/) const noexcept {
      return iface {};
    }
  };

  [[nodiscard]] static constexpr auto flags() noexcept {
    return parser::skip(u16());
  }

  [[nodiscard]] static constexpr auto this_class(const constant::pool & p) noexcept {
    return cpool_class(p);
  }

  [[nodiscard]] static constexpr auto super_class(const constant::pool & p) noexcept {
    return cpool_class(p);
  }

  [[nodiscard]] static constexpr auto interfaces(const constant::pool & p) noexcept {
    return u16() >> [p](uint16_t size) noexcept {
      return parser::exactly(size, cpool_class(p), iface {});
    };
  }

  template<typename Alloc>
  [[nodiscard]] static constexpr auto file(Alloc & alloc) noexcept {
    return (magic_version() & cpool(alloc) + flags()) >> this_class >> super_class >> interfaces;
  }
}

using namespace m4c0::espresso;

static_assert(*u16()("\0\3") == 3); // Paranoid byte-order test

static_assert(*u8()(cls_file) == 0xCA);    // NOLINT
static_assert(*u16()(cls_file) == 0xCAFE); // NOLINT
static_assert(*u32()(cls_file) == jclass_magic_number);

static_assert([] {
  std::array<constant::item, std::numeric_limits<uint16_t>::max()> buffer;
  const auto alloc = [&buffer](uint16_t /*size*/) {
    return buffer.data();
  };
  return file(alloc)(cls_file);
}());

int main() {
}
