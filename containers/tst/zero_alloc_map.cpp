#include "m4c0/containers/zero_alloc_map.hpp"

using namespace m4c0::containers;

class my_key {
  int m_i;

public:
  constexpr my_key() = default;
  constexpr my_key(int i) : m_i(i) { // NOLINT - implicit constructor
  }

  [[nodiscard]] constexpr bool operator==(const my_key & o) const noexcept {
    return m_i == o.m_i;
  }
  [[nodiscard]] constexpr int operator*() const noexcept {
    return m_i;
  }
};

template<>
struct std::hash<my_key> {
  [[nodiscard]] constexpr std::size_t operator()(const my_key & key) const noexcept {
    // Super dumb hash to help test collisions
    return *key;
  }
};

static constexpr auto create_map() {
  using map_t = zero_alloc_map<my_key, char, 3, 2>;

  map_t map;
  map[0] = 'a';
  map[1] = 'b';
  map[2] = 'c';

  // conflicts + keys larger than array
  map[0 + 3 * 3] = 'd';
  map[1 + 3 * 3] = 'e';
  map[2 + 3 * 3] = 'f';
  return map;
}
constexpr const auto map = create_map();

static_assert(map[0] == 'a');
static_assert(map[1] == 'b');
static_assert(map[2] == 'c');
static_assert(map[0 + 3 * 3] == 'd');
static_assert(map[1 + 3 * 3] == 'e');
static_assert(map[2 + 3 * 3] == 'f');

static_assert(map.contains(0));
static_assert(map.contains(0 + 3 * 3));

int main() {
}
