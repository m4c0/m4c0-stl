#pragma once

#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/nil.hpp"
#include "m4c0/parser/traits.hpp"

namespace m4c0::parser {
  template<typename Fn, typename P>
  requires is_parser<P> && accepts<Fn, P>
  constexpr auto operator&(P && p, Fn && fn) noexcept {
    return [fn, p](std::string_view in) {
      return p(in) & fn;
    };
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  constexpr auto operator&(PA && a, PB && b) noexcept {
    return [a, b](std::string_view in) {
      return a(in) & [b](auto /*ra*/, auto in) {
        return b(in);
      };
    };
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  constexpr auto operator+(PA && a, PB && b) noexcept {
    return [a, b](std::string_view in) {
      return a(in) & [b](auto ra, auto in) {
        return b(in) & [ra](auto rb) {
          return ra + rb;
        };
      };
    };
  }

  template<typename P>
  requires is_parser<P>
  constexpr auto operator|(P && p, result_of_t<P> otherwise) noexcept {
    return [p, otherwise](std::string_view in) {
      return p(in) | otherwise;
    };
  }

  template<typename P>
  requires is_parser<P>
  constexpr auto operator|(P && p, std::string_view msg) noexcept {
    return p | failure<>(msg);
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  constexpr auto operator|(PA && a, PB && b) noexcept {
    return [a, b](std::string_view in) {
      return a(in) | b(in);
    };
  }

  template<typename P>
  requires is_parser<P>
  constexpr auto skip(P && p) noexcept {
    return [p](std::string_view in) {
      return p(in) & [](auto /*r*/) {
        return nil {};
      };
    };
  }
}
