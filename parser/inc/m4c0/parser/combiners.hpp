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
    return [p, fn](input_t in) noexcept(nothrows_v<Fn, P>) {
      auto r = p(in);
      if (!r) return std::move(r);
      if constexpr (std::is_member_function_pointer_v<Fn>) {
        if ((*r.*fn)()) return std::move(r);
      } else {
        if (fn(*r)) return std::move(r);
      }
      return result { failure<type_of_t<P>>("Mismatched condition"), in };
    };
  }

  template<typename Fn, typename P>
  requires is_parser<P> && accepts<Fn, P> && not_a_parser<Fn>
  static constexpr auto operator&(P && p, Fn && fn) noexcept {
    return [fn, p](input_t in) noexcept(nothrows_v<Fn, P>) {
      return p(in).map(fn);
    };
  }

  template<typename Tp, typename P>
  requires is_parser<P> && cant_accept<Tp, P> && not_a_parser<Tp>
  static constexpr auto operator&(P && p, Tp && v) noexcept {
    return p & constant(v);
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto operator&(PA && a, PB && b) noexcept {
    return a & [b](auto /*r*/, input_t rem) noexcept(nothrows_v<PA, PB>) {
      return b(rem);
    };
  }

  template<typename PA, typename PB, typename Fn>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto combine(PA && a, PB && b, Fn && fn) noexcept {
    using a_t = type_of_t<PA>;
    using b_t = type_of_t<PB>;
    using res_t = std::decay_t<std::invoke_result_t<Fn, a_t, b_t>>;
    constexpr const auto is_no_except = nothrows_v<PA, PB> && std::is_nothrow_invocable_v<Fn, a_t, b_t>;
    return [a, b, fn = std::forward<Fn>(fn)](input_t in) noexcept(is_no_except) -> result<res_t> {
      auto ra = a(in);
      if (!ra) return ra.template as_failure<res_t>();

      auto rb = b(ra.remainder());
      if (!rb) return rb.template as_failure<res_t>();

      return { fn(std::move(*ra), std::move(*rb)), rb.remainder() };
    };
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto operator+(PA && a, PB && b) noexcept {
    return combine(a, b, std::plus<>());
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator+(type_of_t<P> init, P && p) noexcept {
    return constant(init) + p;
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator|(P && p, type_of_t<P> otherwise) noexcept {
    return p | constant(otherwise);
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator|(P && p, result_of_t<P> otherwise) noexcept {
    return [p, otherwise](input_t in) noexcept(p(in)) {
      return p(in) | otherwise;
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto operator|(P && p, input_t msg) noexcept {
    return p | fail<type_of_t<P>>(msg);
  }

  template<typename PA, typename PB>
  requires is_parser<PA> && is_parser<PB>
  static constexpr auto operator|(PA && a, PB && b) noexcept {
    return [a, b](input_t in) noexcept(nothrows_v<PA, PB>) {
      // a(in) | b(in) would be just fine, but it process both due to C++ rules
      auto r = a(in);
      if (r) return r;
      return b(in);
    };
  }

  template<typename P, typename Fn>
  requires is_parser<P> && is_parser<std::invoke_result_t<Fn, type_of_t<P>>>
  static constexpr auto operator>>(P && p, Fn && fn) noexcept {
    return p & [fn](auto r, input_t rem) noexcept(nothrows_v<Fn, P>) {
      return fn(r)(rem);
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
    return [p0, pn](input_t in) noexcept(nothrows_v<P0, PN>) {
      auto res = p0(in);
      while (res) {
        auto next = pn(res.remainder());
        if (!next) break;
        res = result { std::move(*res) + std::move(*next), next.remainder() };
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
      for (unsigned i = 0; i < n && res; ++i) {
        auto next = p(res.remainder());
        res = next.map([r = std::move(*res)](auto n) noexcept {
          return r + n;
        });
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
        auto next = p(res.remainder());
        if (!next) break;
        res = next.map([r = std::move(*res)](auto n) noexcept {
          return r + n;
        });
      }
      return res;
    };
  }

  template<typename P>
  requires is_parser<P>
  static constexpr auto look_ahead(P && p) noexcept {
    return [p](input_t in) noexcept -> result<nil> {
      auto res = p(in);
      if (!res) return res.template as_failure<nil>();
      return { nil {}, in };
    };
  }
}
