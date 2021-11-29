#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <type_traits>

template<typename Tp>
class ce_node {
  Tp m_value {};
  ce_node<Tp> * m_next {};

public:
  using self_t = ce_node<Tp>;

  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using pointer = Tp *;
  using reference = Tp &;
  using value_type = Tp;

  constexpr ce_node() = default;
  constexpr explicit ce_node(Tp t) noexcept : m_value(t) {
  }

  [[nodiscard]] constexpr bool operator==(const self_t & o) const noexcept {
    return m_value == o.m_value;
  }
  [[nodiscard]] constexpr bool operator==(reference o) const noexcept {
    return m_value == o;
  }
  [[nodiscard]] constexpr bool operator==(value_type o) const noexcept {
    return m_value == o;
  }

  [[nodiscard]] constexpr self_t operator++() noexcept {
    *this = m_next ? *m_next : self_t {};
    return *this;
  }

  [[nodiscard]] constexpr value_type operator*() const noexcept {
    return m_value;
  }

  constexpr void set_next(self_t * n) noexcept {
    m_next = n;
  }
};
using ni = ce_node<int>;

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

template<typename AllocTp, typename Tp>
concept allocator = requires(AllocTp a, Tp t) {
  { a.allocate() } -> std::same_as<ce_node<Tp> *>;
};

template<typename Tp, allocator<Tp> AllocTp>
class ce_list {
  AllocTp * m_alloc;
  ce_node<Tp> * m_head {};
  ce_node<Tp> * m_tail {};

public:
  constexpr explicit ce_list(AllocTp * a) : m_alloc(a) {
  }

  constexpr void push_back(Tp t) noexcept {
    auto * n = m_alloc->allocate();
    *n = ce_node<int> { t };

    if (!m_head) {
      m_head = m_tail = n;
    } else {
      m_tail->set_next(n);
      m_tail = n;
    }
  }

  [[nodiscard]] constexpr ce_node<Tp> begin() const noexcept {
    return m_head ? *m_head : ce_node<Tp> {};
  }
  [[nodiscard]] constexpr ce_node<Tp> end() const noexcept {
    return {};
  }
};

class alloc {
  std::array<ce_node<int>, 3> m_buffer {};
  int m_pos {};

public:
  constexpr ce_node<int> * allocate() {
    return &m_buffer.at(m_pos++);
  }
};
static_assert([] {
  alloc al;
  ce_list<int, alloc> l { &al };
  return l.begin() == l.end();
}());
static_assert([] {
  alloc al;
  ce_list<int, alloc> l { &al };
  l.push_back(1);
  return l.begin() == 1 && ++l.begin() == l.end();
}());
static_assert([] {
  alloc al;

  ce_list<int, alloc> l { &al };
  l.push_back(1);
  l.push_back(2);
  l.push_back(4);

  constexpr const auto a = std::array { 1, 2, 4 };
  return std::equal(l.begin(), l.end(), a.begin(), a.end());
}());
