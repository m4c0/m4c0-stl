#pragma once

#include <optional>
#include <string_view>
#include <type_traits>
#include <variant>

namespace m4c0::parser {
  template<typename ResTp>
  class success {
    ResTp m_value;
    std::string_view m_remainder;

  public:
    constexpr explicit success(ResTp v, std::string_view r) : m_value(v), m_remainder(r) {};

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp, std::string_view>
    constexpr auto map(Fn && fn) const noexcept {
      return fn(m_value, m_remainder);
    }

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp>
    constexpr auto map(Fn && fn) const noexcept {
      using res_t = std::invoke_result_t<Fn, ResTp>;
      return success<res_t> { fn(m_value), m_remainder };
    }

    [[nodiscard]] constexpr bool operator==(const success & o) const noexcept {
      return m_value == o.m_value && m_remainder == o.m_remainder;
    }
  };

  template<typename ResTp = void>
  class failure {
    // TODO: find a constexpr way of storing dynamic strings
    std::string_view m_message;

    template<typename Tp>
    friend class failure;

  public:
    template<typename Tp>
    constexpr explicit failure(failure<Tp> f) : m_message(f.m_message) {};
    constexpr explicit failure(std::string_view msg) : m_message(msg) {};

    [[nodiscard]] constexpr bool operator==([[maybe_unused]] const failure & o) const noexcept {
      return m_message == o.m_message;
    }
  };

  template<typename ResTp>
  class result {
    std::variant<success<ResTp>, failure<ResTp>> m_value;

    [[nodiscard]] constexpr const auto & get_failure() const noexcept {
      return std::get<failure<ResTp>>(m_value);
    }
    [[nodiscard]] constexpr const auto & get_success() const noexcept {
      return std::get<success<ResTp>>(m_value);
    }

  public:
    using type = ResTp;

    constexpr result(success<ResTp> t) : m_value(t) { // NOLINT
    }
    template<typename Tp>
    constexpr result(failure<Tp> t) : m_value(failure<ResTp>(t)) { // NOLINT
    }

    [[nodiscard]] constexpr bool operator==(const result<ResTp> & o) const noexcept {
      return m_value == o.m_value;
    }

    [[nodiscard]] constexpr const result<ResTp> & operator|(const result<ResTp> & o) const noexcept {
      return *this ? *this : o;
    }
    [[nodiscard]] constexpr const result<ResTp> & operator&(const result<ResTp> & o) const noexcept {
      return !*this ? *this : o;
    }

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp, std::string_view>
    constexpr auto operator&(Fn && fn) const noexcept {
      using res_t = std::invoke_result_t<Fn, ResTp, std::string_view>;
      return !*this ? res_t { get_failure() } : get_success().map(fn);
    }

    template<typename Fn>
    requires std::is_invocable_v<Fn, ResTp>
    constexpr auto operator&(Fn && fn) const noexcept {
      using res_t = result<std::invoke_result_t<Fn, ResTp>>;
      return !*this ? res_t { get_failure() } : res_t { get_success().map(fn) };
    }

    [[nodiscard]] constexpr explicit operator bool() const noexcept {
      return std::holds_alternative<success<ResTp>>(m_value);
    }
  };
  template<typename ResTp>
  result(success<ResTp>) -> result<ResTp>;
  template<typename ResTp>
  result(failure<ResTp>) -> result<ResTp>;
}
