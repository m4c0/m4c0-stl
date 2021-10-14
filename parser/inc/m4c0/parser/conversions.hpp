#pragma once

namespace m4c0::parser {
  template<typename Tp>
  static constexpr auto to() noexcept {
    return [](auto v) noexcept -> Tp {
      return Tp { v };
    };
  }
}
