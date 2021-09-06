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
    [[nodiscard]] constexpr auto map(Fn && fn) const noexcept {
      return success<std::invoke_result_t<Fn, ResTp>>(fn(m_value), m_remainder);
    }

    [[nodiscard]] constexpr bool operator==(const success & o) const noexcept {
      return m_value == o.m_value && m_remainder == o.m_remainder;
    }
  };

  template<typename ResTp>
  class failure {
    // TODO: find a constexpr way of storing dynamic strings
    std::string_view m_message;

  public:
    constexpr explicit failure(std::string_view msg) : m_message(msg) {};

    [[nodiscard]] constexpr auto error() const noexcept {
      return m_message;
    }

    template<typename Fn>
    [[nodiscard]] constexpr auto map(Fn && /*fn*/) const noexcept {
      return failure<std::invoke_result_t<Fn, ResTp>>(m_message);
    }

    [[nodiscard]] constexpr bool operator==([[maybe_unused]] const failure & o) const noexcept {
      return m_message == o.m_message;
    }
  };

  template<typename ResTp>
  class result {
    std::variant<success<ResTp>, failure<ResTp>> m_value;

  public:
    using type = ResTp;

    constexpr result(success<ResTp> t) : m_value(t) { // NOLINT
    }
    constexpr result(failure<ResTp> t) : m_value(t) { // NOLINT
    }

    [[nodiscard]] constexpr bool operator==(const result<ResTp> & o) const noexcept {
      return m_value == o.m_value;
    }

    template<typename Fn>
    [[nodiscard]] constexpr auto map(Fn && fn) const noexcept {
      return std::visit(
          [fn](auto && v) -> result<std::invoke_result_t<Fn, ResTp>> {
            return v.map(fn);
          },
          m_value);
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
