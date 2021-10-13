#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/result.hpp"
#include "m4c0/parser/str.hpp"
#include "m4c0/parser/tokeniser.hpp"

#include <variant>

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
  constexpr const auto jclass_magic_number = 0xCAFEBABE;
  constexpr const auto latest_supported_version = 0x37; // Java SE 11
  constexpr const auto first_supported_version = 0x2D;  // JDK 1.1

  [[nodiscard]] static constexpr auto is_supported_major_version(uint16_t n) noexcept {
    return n >= first_supported_version && n <= latest_supported_version;
  }

  [[nodiscard]] static constexpr auto u8() noexcept {
    return parser::any_char() & [](char c) noexcept -> uint8_t {
      return static_cast<uint8_t>(c);
    };
  }
  [[nodiscard]] static constexpr auto u16() noexcept {
    return parser::combine(u8(), u8(), [](uint8_t a, uint8_t b) noexcept -> uint16_t {
      return (a << 8U) | b; // NOLINT
    });
  }
  [[nodiscard]] static constexpr auto u32() noexcept {
    return parser::combine(u16(), u16(), [](uint16_t a, uint16_t b) noexcept -> uint32_t {
      return (a << 16U) | b; // NOLINT
    });
  }

  [[nodiscard]] static constexpr auto match_u8(uint8_t n) noexcept {
    return u8() && [n](uint8_t o) noexcept {
      return n == o;
    };
  }
  [[nodiscard]] static constexpr auto match_u32(uint32_t n) noexcept {
    return u32() && [n](uint32_t o) noexcept {
      return n == o;
    };
  }

  [[nodiscard]] static constexpr auto magic() noexcept {
    return match_u32(jclass_magic_number) | "Invalid magic number";
  }
  [[nodiscard]] static constexpr auto minor_version() noexcept {
    return u16();
  }
  [[nodiscard]] static constexpr auto major_version() noexcept {
    return (u16() && is_supported_major_version) | "Invalid/unknown major version";
  }

  struct cls {
    uint16_t name_index;
  };
  struct method {
    uint16_t class_index;
    uint16_t name_and_type_index;
  };
  struct name_type {
    uint16_t name_index;
    uint16_t description_index;
  };
  struct utf8 {
    parser::token<void> bytes;
  };
  using cpool_item = std::variant<cls, method, name_type, utf8>;

  struct pool {
    constexpr pool operator+(const cpool_item & /*r*/) const noexcept {
      return pool {};
    }
  };

  [[nodiscard]] static constexpr auto constant_class_ref() noexcept {
    constexpr const auto id = 7;
    return match_u8(id) & u16() & [](uint16_t c) noexcept {
      return cpool_item { cls { c } };
    };
  }

  [[nodiscard]] static constexpr auto constant_method_ref() noexcept {
    constexpr const auto id = 10;
    return match_u8(id) & parser::combine(u16(), u16(), [](uint16_t c, uint16_t nt) noexcept {
             return cpool_item { method { c, nt } };
           });
  }

  [[nodiscard]] static constexpr auto constant_name_type() noexcept {
    constexpr const auto id = 12;
    return match_u8(id) & parser::combine(u16(), u16(), [](uint16_t c, uint16_t nt) noexcept {
             return cpool_item { name_type { c, nt } };
           });
  }

  [[nodiscard]] static constexpr auto constant_utf8() noexcept {
    constexpr const auto id = 1;
    return match_u8(id) & u16() & [](uint16_t size, auto rem) noexcept {
      using namespace m4c0::parser;
      const auto p = tokenise<void>(exactly(size, skip(any_char())));
      return p(rem) & [](token<void> t) noexcept {
        return cpool_item { utf8 { t } };
      };
    };
  }

  [[nodiscard]] static constexpr auto constant() noexcept {
    return constant_class_ref() | constant_method_ref() | constant_name_type() | constant_utf8();
  }

  [[nodiscard]] static constexpr auto cpool_size() noexcept {
    return u16() & [](uint16_t n) noexcept {
      return n - 1;
    };
  }
  [[nodiscard]] static constexpr auto cpool() noexcept {
    return cpool_size() & [](uint16_t size, auto rem) noexcept {
      const auto p = parser::exactly(size, constant(), pool {});
      return p(rem);
    };
  }

  [[nodiscard]] static constexpr auto flags() noexcept {
    return u16();
  }

  [[nodiscard]] static constexpr auto this_class() noexcept {
    return u16();
  }

  [[nodiscard]] static constexpr auto super_class() noexcept {
    return u16();
  }

  [[nodiscard]] static constexpr auto file() noexcept {
    return magic() & minor_version() & major_version() & cpool() & flags() & this_class() & super_class();
  }
}

using namespace m4c0::espresso;

static_assert(*u16()("\0\3") == 3); // Paranoid byte-order test

static_assert(*u8()(cls_file) == 0xCA);    // NOLINT
static_assert(*u16()(cls_file) == 0xCAFE); // NOLINT
static_assert(*u32()(cls_file) == jclass_magic_number);

static_assert(file()(cls_file));

int main() {
}
