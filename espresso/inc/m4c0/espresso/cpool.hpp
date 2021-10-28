#pragma once

#include "m4c0/espresso/base_parsing.hpp"
#include "m4c0/parser/tokeniser.hpp"

#include <variant>

namespace m4c0::espresso::constant {
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

  using item = std::variant<cls, method, name_type, utf8>;
}
namespace m4c0::espresso {
  class cpool_items {
    unsigned m_size {};

    explicit constexpr cpool_items(unsigned s) : m_size(s) {
    }

  public:
    constexpr cpool_items() = default;

    [[nodiscard]] constexpr cpool_items operator+(const constant::item & /*r*/) const noexcept {
      return cpool_items { m_size + 1 };
    }

    [[nodiscard]] constexpr bool contains(unsigned idx) const noexcept {
      return idx < m_size;
    }
  };

  [[nodiscard]] static constexpr auto constant_class_ref() noexcept {
    constexpr const auto id = 7;
    return match_u8(id) & u16() & [](uint16_t c) noexcept -> constant::item {
      return constant::cls { c };
    };
  }

  [[nodiscard]] static constexpr auto constant_method_ref() noexcept {
    constexpr const auto id = 10;
    return match_u8(id) & parser::combine(u16(), u16(), [](uint16_t c, uint16_t nt) noexcept -> constant::item {
             return constant::method { c, nt };
           });
  }

  [[nodiscard]] static constexpr auto constant_name_type() noexcept {
    constexpr const auto id = 12;
    return match_u8(id) & parser::combine(u16(), u16(), [](uint16_t c, uint16_t nt) noexcept -> constant::item {
             return constant::name_type { c, nt };
           });
  }

  [[nodiscard]] static constexpr auto constant_utf8() noexcept {
    constexpr const auto id = 1;
    return match_u8(id) & u16() & [](uint16_t size, auto rem) noexcept {
      using namespace m4c0::parser;
      const auto p = tokenise<void>(exactly(size, skip(any_char())));
      return p(rem) & [](token<void> t) noexcept -> constant::item {
        return constant::utf8 { t };
      };
    };
  }

  [[nodiscard]] static constexpr auto constant_item() noexcept {
    return constant_class_ref() | constant_method_ref() | constant_name_type() | constant_utf8();
  }

  [[nodiscard]] static constexpr auto cpool_size() noexcept {
    return u16() & [](uint16_t n) noexcept {
      return n - 1;
    };
  }
  [[nodiscard]] static constexpr auto cpool() noexcept {
    return cpool_size() >> [](uint16_t size) noexcept {
      return parser::exactly(size, constant_item(), cpool_items {});
    };
  }

  [[nodiscard]] static constexpr auto cpool_class(const cpool_items & p) noexcept {
    const auto contains = [p](uint16_t idx) noexcept {
      return p.contains(idx);
    };
    return (u16() && contains) & parser::constant(p);
  }

}
