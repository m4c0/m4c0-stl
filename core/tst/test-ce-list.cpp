#include "m4c0/ce_list.hpp"

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <type_traits>

using ni = m4c0::ce_list_node<int>;

static_assert(*ni {} == 0);
static_assert(*ni {} != 1);
static_assert(*ni { 1 } == 1);
static_assert(*ni { 1 } != 2);

static_assert(ni {} == 0);
static_assert(ni {} != 1);
static_assert(ni { 1 } == 1);
static_assert(ni { 1 } != 2);

static_assert(ni {} == ni {});
static_assert(ni {} != ni { 1 });
static_assert(ni { 1 } == ni { 1 });
static_assert(ni { 1 } != ni { 2 });

static_assert([] {
  ni a { 1 };
  ni b { 2 };
  ni c {};
  a.set_next(&b);
  b.set_next(&c);
  return ++a == b && ++b == c && ++c == ni {};
}());

class alloc {
  std::array<ni, 3> m_buffer {};
  int m_pos {};

public:
  constexpr ni * allocate() {
    return &m_buffer.at(m_pos++);
  }
};
using li = m4c0::ce_list<int, alloc>;

static_assert([] {
  alloc al;
  li l { &al };
  return l.begin() == l.end();
}());
static_assert([] {
  alloc al;
  li l { &al };
  l.push_back(1);
  return l.begin() == 1 && ++l.begin() == l.end();
}());
static_assert([] {
  alloc al;

  li l { &al };
  l.push_back(1);
  l.push_back(2);
  l.push_back(4);

  constexpr const auto a = std::array { 1, 2, 4 };
  return std::equal(l.begin(), l.end(), a.begin(), a.end());
}());

int main() {
}
