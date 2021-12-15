#pragma once

#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/constants.hpp"
#include "m4c0/parser/nil.hpp"
#include "m4c0/parser/traits.hpp"

#include <type_traits>

namespace m4c0::parser {
  template<typename P, typename Fn>
  requires is_parser<P> && accepts<Fn, P>
  static constexpr auto operator&&(P && p, Fn && fn) noexcept {
    return [p, fn](input_t in) noexcept {
      const auto r = p(in);
      if (!r) return r;
      if (*(r & fn)) return r;
      return result { failure<type_of_t<P>>("Mismatched condition"), in };
    };
  }

  template<typename Fn, typename P>
  requires is_parser<P> && accepts<Fn, P> && not_a_parser<Fn>
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
      // a(in) | b(in) would be just fine, but it process both due to C++ rules
      const auto r = a(in);
      if (r) return r;
      return b(in);
    };
  }

  template<typename P, typename Fn>
  requires is_parser<P> && is_parser<std::invoke_result_t<Fn, type_of_t<P>>>
  static constexpr auto operator>>(P && p, Fn && fn) noexcept {
    return [p, fn](input_t in) noexcept {
      return p(in) & [fn](auto r, input_t rem) noexcept {
        return fn(r)(rem);
      };
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto skip(P && p) noexcept {
    return p & nil {};
  }

  template<typename P0, typename PN>
  requires is_parser<P0> && is_parser<PN>
  static constexpr auto operator<<(P0 && p0, PN && pn) noexcept {
    return [p0, pn](input_t in) noexcept {
      auto res = p0(in);
      while (res && !in.empty()) {
        auto next = res & [pn](auto r1, input_t rem) noexcept {
          return pn(rem) & [r1 = std::move(r1)](auto r2) mutable noexcept {
            return r1 + r2;
          };
        };
        if (!next) break;
        res = std::move(next);
      }
      return res;
    };
  }

  template<typename P, typename Tp = type_of_t<P>>
  requires is_parser<P>
  static constexpr auto many(P && p, Tp init = Tp {}) noexcept {
    return constant(init) << p;
  }

  template<typename P, typename Tp = type_of_t<P>>
  requires is_parser<P>
  static constexpr auto at_least_one(P && p, Tp init = Tp {}) noexcept {
    return constant(init) + p << p;
  }

  template<typename P, typename Tp = type_of_t<P>>
  requires is_parser<P>
  static constexpr auto exactly(unsigned n, P && p, Tp init = Tp {}) noexcept {
    return [n, p, init = constant(init)](input_t in) noexcept {
      auto res = init(in);
      for (unsigned i = 0; i < n; ++i) {
        const auto next = res & [p](auto r1, input_t rem) noexcept {
          return p(rem) & [r1](auto r2) noexcept {
            return r1 + r2;
          };
        };
        if (!next) return next;
        res = next;
      }
      return res;
    };
  }

  template<typename P, typename Tp = type_of_t<P>>
  requires is_parser<P>
  static constexpr auto at_most(unsigned n, P && p, Tp init = Tp {}) noexcept {
    // TODO: this is nearly the same as "exactly" - is there a way define one using the other?
    return [n, p, init = constant(init)](input_t in) noexcept {
      auto res = init(in);
      for (unsigned i = 0; i < n; ++i) {
        const auto next = res & [p](auto r1, input_t rem) noexcept {
          return p(rem) & [r1](auto r2) noexcept {
            return r1 + r2;
          };
        };
        if (!next) break;
        res = next;
      }
      return res;
    };
  }
}
