#pragma once

#include <utility>

namespace m4c0::parser {
  struct nil {};

  [[nodiscard]] constexpr bool operator==(nil /*unused*/, nil /*unused*/) noexcept {
    return true;
  }

  [[nodiscard]] constexpr auto operator+(nil /*unused*/, nil /*unused*/) noexcept {
    return nil {};
  }

  template<typename Tp>
  [[nodiscard]] constexpr decltype(auto) operator+(nil /*unused*/, Tp && v) noexcept {
    return std::forward<Tp>(v);
  }

  template<typename Tp>
  [[nodiscard]] constexpr decltype(auto) operator+(Tp && v, nil /*unused*/) noexcept {
    return std::forward<Tp>(v);
  }
}
