#pragma once

#include <concepts>
#include <cstddef>
#include <iterator>

namespace m4c0 {
  template<typename Tp>
  class ce_list_node {
    Tp m_value {};
    ce_list_node<Tp> * m_next {};

  public:
    using self_t = ce_list_node<Tp>;

    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using pointer = Tp *;
    using reference = Tp &;
    using value_type = Tp;

    constexpr ce_list_node() = default;
    constexpr explicit ce_list_node(Tp t) noexcept : m_value(t) {
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

  template<typename AllocTp, typename Tp>
  concept list_node_allocator = requires(AllocTp a, Tp t) {
    { a.allocate() } -> std::same_as<m4c0::ce_list_node<Tp> *>;
  };

  template<typename Tp, list_node_allocator<Tp> AllocTp>
  class ce_list {
    using node_t = ce_list_node<Tp>;

    AllocTp * m_alloc;
    node_t * m_head {};
    node_t * m_tail {};

  public:
    constexpr explicit ce_list(AllocTp * a) : m_alloc(a) {
    }

    constexpr void push_back(Tp t) noexcept {
      auto * n = m_alloc->allocate();
      *n = ce_list_node<Tp> { t };

      if (!m_head) {
        m_head = m_tail = n;
      } else {
        m_tail->set_next(n);
        m_tail = n;
      }
    }

    [[nodiscard]] constexpr node_t begin() const noexcept {
      return m_head ? *m_head : node_t {};
    }
    [[nodiscard]] constexpr node_t end() const noexcept {
      return {};
    }
  };
}
