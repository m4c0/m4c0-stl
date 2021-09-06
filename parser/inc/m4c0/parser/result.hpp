#pragma once

#include <optional>
#include <string_view>
#include <variant>

namespace m4c0::parser {
  template<typename ResTp>
  class success {
    ResTp m_value;
    std::string_view m_remainder;

  public:
    constexpr explicit success(ResTp v, std::string_view r) : m_value(v), m_remainder(r) {};

    [[nodiscard]] constexpr std::string_view remainder() const noexcept {
      return m_remainder;
    }

    [[nodiscard]] constexpr ResTp value() const noexcept {
      return m_value;
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

    [[nodiscard]] constexpr auto message() const noexcept {
      return m_message;
    }

    [[nodiscard]] constexpr bool operator==([[maybe_unused]] const failure & o) const noexcept {
      return m_message == o.m_message;
    }
  };

  template<typename ResTp>
  class result {
    std::variant<success<ResTp>, failure<ResTp>> m_value;

  public:
    constexpr result(success<ResTp> t) : m_value(t) { // NOLINT
    }
    constexpr result(failure<ResTp> t) : m_value(t) { // NOLINT
    }

    [[nodiscard]] constexpr std::optional<std::string_view> error() const noexcept {
      if (*this) {
        return std::nullopt;
      }
      return std::get<failure<ResTp>>(m_value).message();
    }

    [[nodiscard]] constexpr std::optional<ResTp> value() const noexcept {
      if (!*this) {
        return std::nullopt;
      }
      return std::get<success<ResTp>>(m_value).value();
    }

    [[nodiscard]] constexpr bool operator==(const result<ResTp> & o) const noexcept {
      return m_value == o.m_value;
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
