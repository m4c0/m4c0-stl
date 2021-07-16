#include "m4c0/ce_map.hpp"

#include <algorithm>
#include <array>
#include <initializer_list>
#include <optional>
#include <stdexcept>
#include <type_traits>

// It can be const-constructed
static_assert([] {
  const m4c0::ce_map<int, char, 2> map {
    { 3, 'a' },
    { 0, 'b' },
  };
  return map[3] == 'a' && map[0] == 'b';
}());
static_assert([] {
  // This can be simplified in GCC as "pair { k, v }, { k2, v2 }", but Clang fails to deduce the remaining parameters
  const m4c0::ce_map map = {
    m4c0::pair { 3, 'a' },
    m4c0::pair { 0, 'b' },
    m4c0::pair { 1, 'd' },
  };
  return map[3] == 'a' && map[0] == 'b' && map[1] == 'd';
}());

// It can be constructed as a parameter
static_assert([](m4c0::ce_map<unsigned, char, 1> map) {
  return map[3] == 'a';
}({ m4c0::pair { 3U, 'a' } }));

// It can return a default value
static_assert([] {
  const m4c0::ce_map map { m4c0::pair { 10, 'a' } };
  return map.get_or_else(10, 'b') == 'a' && map.get_or_else(20, 'c') == 'c';
}());

int main() {
}
