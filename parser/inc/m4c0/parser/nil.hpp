#pragma once

namespace m4c0::parser {
  struct nil {};

  [[nodiscard]] constexpr bool operator==(nil /*unused*/, nil /*unused*/) {
    return true;
  }

  template<typename Tp>
  [[nodiscard]] constexpr auto operator+(Tp && v, nil /*unused*/) {
    return v;
  }
}
