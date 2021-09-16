#pragma once

#include "m4c0/parser/string_view.hpp"

#include <type_traits>

namespace m4c0::parser {
  using input_t = string_view;

  template<typename ResTp>
  class success {
    ResTp m_value;
    input_t m_remainder;

  public:
    constexpr explicit success(ResTp v, input_t r) noexcept : m_value(v), m_remainder(r) {};

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp, input_t>
    constexpr auto map(Fn && fn) const noexcept {
      return fn(m_value, m_remainder);
    }

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp>
    constexpr auto map(Fn && fn) const noexcept {
      using res_t = std::invoke_result_t<Fn, ResTp>;
      if constexpr (std::is_member_function_pointer_v<std::decay_t<Fn>>) {
        return success<res_t> { (m_value.*fn)(), m_remainder };
      } else {
        return success<res_t> { fn(m_value), m_remainder };
      }
    }

    [[nodiscard]] constexpr bool operator==(const success & o) const noexcept {
      return m_value == o.m_value && m_remainder == o.m_remainder;
    }
    [[nodiscard]] constexpr auto operator*() const noexcept {
      return m_value;
    }
  };

  template<typename ResTp = void>
  class failure {
    // TODO: find a constexpr way of storing dynamic strings
    input_t m_message;

    template<typename Tp>
    friend class failure;

  public:
    template<typename Tp>
    constexpr explicit failure(failure<Tp> f) noexcept : m_message(f.m_message) {};
    constexpr explicit failure(input_t msg) noexcept : m_message(msg) {};

    [[nodiscard]] constexpr bool operator==([[maybe_unused]] const failure & o) const noexcept {
      return m_message == o.m_message;
    }
  };

  template<typename ResTp>
  class result {
    union value {
      success<ResTp> s;
      failure<ResTp> f;
    };
    value m_value;
    bool m_success;

    [[nodiscard]] constexpr const auto & get_failure() const noexcept {
      return m_value.f;
    }
    [[nodiscard]] constexpr const auto & get_success() const noexcept {
      return m_value.s;
    }

  public:
    using type = ResTp;

    constexpr result(success<ResTp> t) noexcept : m_value { t }, m_success { true } { // NOLINT
    }
    template<typename Tp>
    constexpr result(failure<Tp> t) noexcept // NOLINT
      : m_value { .f = failure<ResTp>(t) }
      , m_success { false } {
    }

    [[nodiscard]] constexpr bool operator==(const result<ResTp> & o) const noexcept {
      if (m_success != o.m_success) return false;
      if (m_success) {
        return get_success() == o.get_success();
      }
      return get_failure() == o.get_failure();
    }

    [[nodiscard]] constexpr const result<ResTp> & operator|(const result<ResTp> & o) const noexcept {
      return *this ? *this : o;
    }
    [[nodiscard]] constexpr const result<ResTp> & operator&(const result<ResTp> & o) const noexcept {
      return !*this ? *this : o;
    }

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp, input_t>
    constexpr auto operator&(Fn && fn) const noexcept {
      using res_t = std::invoke_result_t<Fn, ResTp, input_t>;
      return !*this ? res_t { get_failure() } : get_success().map(fn);
    }

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp>
    constexpr auto operator&(Fn && fn) const noexcept {
      using res_t = result<std::invoke_result_t<Fn, ResTp>>;
      return !*this ? res_t { get_failure() } : res_t { get_success().map(fn) };
    }

    [[nodiscard]] constexpr explicit operator bool() const noexcept {
      return m_success;
    }

    [[nodiscard]] constexpr ResTp operator*() const noexcept {
      // Deref of a failure is UB.
      return m_success ? *get_success() : ResTp {};
    }
  };
  template<typename ResTp>
  result(success<ResTp>) -> result<ResTp>;
  template<typename ResTp>
  result(failure<ResTp>) -> result<ResTp>;
}
