#include "m4c0/containers/unique_array.hpp"

#include <algorithm>

using m4c0::containers::unique_array;

using uint = unique_array<int>;

static_assert(!uint());
static_assert(uint().size() == 0);
static_assert(uint(3));
static_assert(uint(3).size() == 3);

static constexpr auto algo_gen() noexcept {
  uint res { 3 };
  std::generate(std::begin(res), std::end(res), [i = 0]() mutable noexcept {
    return ++i;
  });
  return std::move(res);
}
static constexpr auto idx_gen() noexcept {
  uint res { 3 };
  res[0] = 1;
  res[1] = 2;
  res[2] = 3;
  return std::move(res);
}
static constexpr auto equals(const uint & a, const uint & b) noexcept {
  return std::equal(a.begin(), a.end(), b.begin(), b.end());
}
static_assert(equals(algo_gen(), idx_gen()));

static_assert([] {
  uint a = algo_gen();
  uint b = std::move(a);
  return equals(b, idx_gen());
}());
