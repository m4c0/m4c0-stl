#pragma once

#include <type_traits>

// Contains concepts similar to C++20's. They are here to avoid dealing with broken/outdated STL implementations

namespace m4c0 {
  template<typename Tp, typename OTp>
  concept convertible_to = std::is_convertible_v<Tp, OTp>;

  template<typename Tp, typename OTp>
  concept same_as = std::is_same_v<Tp, OTp>;

  // Non-C++20 concepts

  template<typename Tp>
  concept hashable = requires(Tp v1, Tp v2) {
    { std::hash<Tp> {}(v1) } -> convertible_to<std::size_t>;
    { v1 == v2 };
  };
}
