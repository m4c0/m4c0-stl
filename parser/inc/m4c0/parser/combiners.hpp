#pragma once

#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/nil.hpp"
#include "m4c0/parser/traits.hpp"

namespace m4c0::parser {
  template<typename Fn, typename P>
  requires is_parser<P> && accepts<Fn, P>
  static constexpr auto operator&(P && p, Fn && fn) noexcept {
    return [fn, p](input_t in) noexcept {
      return p(in) & fn;
    };
  }

  template<typename Tp, typename P>
  requires is_parser<P> && cant_accept<Tp, P> && not_a_parser<Tp>
  static constexpr auto operator&(P && p, Tp && v) noexcept {
    return [v, p](input_t in) noexcept {
      return p(in) & [v](auto /*r*/) noexcept {
        return v;
      };
    };
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto operator&(PA && a, PB && b) noexcept {
    return [a, b](input_t in) noexcept {
      return a(in) & [b](auto /*ra*/, auto in) noexcept {
        return b(in);
      };
    };
  }

  template<typename PA, typename PB, typename Fn>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto combine(PA && a, PB && b, Fn && fn) noexcept {
    return [a, b, fn = std::forward<Fn>(fn)](input_t in) noexcept {
      return a(in) & [b, fn](auto ra, auto in) noexcept {
        return b(in) & [ra, fn](auto rb) noexcept {
          return fn(ra, rb);
        };
      };
    };
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto operator+(PA && a, PB && b) noexcept {
    return [a, b](input_t in) noexcept {
      return a(in) & [b](auto ra, auto in) noexcept {
        return b(in) & [ra](auto rb) noexcept {
          return ra + rb;
        };
      };
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator+(type_of_t<P> init, P && p) noexcept {
    return [init, p](input_t in) noexcept {
      return p(in) & [init](auto r) noexcept {
        return init + r;
      };
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator|(P && p, type_of_t<P> otherwise) noexcept {
    return [p, otherwise](input_t in) noexcept {
      return p(in) | result { success { otherwise }, in };
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator|(P && p, result_of_t<P> otherwise) noexcept {
    return [p, otherwise](input_t in) noexcept {
      return p(in) | otherwise;
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator|(P && p, input_t msg) noexcept {
    return [p, msg](input_t in) noexcept {
      return p(in) | failure<>(msg);
    };
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto operator|(PA && a, PB && b) noexcept {
    return [a, b](input_t in) noexcept {
      return a(in) | b(in);
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto skip(P && p) noexcept {
    return p & nil {};
  }

  template<typename P, typename Tp = type_of_t<P>>
  requires is_parser<P>
  static constexpr auto at_least_one(P && p, Tp init = Tp {}) noexcept {
    return [p, init](input_t in) noexcept -> result<Tp> {
      auto res = p(in) & [init](const type_of_t<P> & r) noexcept {
        return init + r;
      };
      while (res && !in.empty()) {
        const auto next = res & [p](const Tp & r1, auto in) noexcept {
          return p(in) & [r1](const type_of_t<P> & r2) noexcept {
            return r1 + r2;
          };
        };
        if (!next) break;
        res = next;
      }
      return res;
    };
  }

  template<typename P, typename Tp = type_of_t<P>>
  requires is_parser<P>
  static constexpr auto many(P && p, Tp init = Tp {}) noexcept {
    return at_least_one(std::forward<P>(p), init) | init;
  }
}
