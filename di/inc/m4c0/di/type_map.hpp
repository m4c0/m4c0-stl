#pragma once

#include "m4c0/di/type_id.hpp"

#include <map>

namespace m4c0::di {
  template<class Tp>
  class type_map {
    using container_t = std::map<int, Tp>;

    container_t m_data;

  public:
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    using reverse_iterator = typename container_t::reverse_iterator;

    [[nodiscard]] iterator begin() {
      return m_data.begin();
    }
    [[nodiscard]] iterator end() {
      return m_data.end();
    }
    [[nodiscard]] const_iterator begin() const {
      return m_data.begin();
    }
    [[nodiscard]] const_iterator end() const {
      return m_data.end();
    }
    [[nodiscard]] const_iterator cbegin() const {
      return m_data.cbegin();
    }
    [[nodiscard]] const_iterator cend() const {
      return m_data.cend();
    }

    [[nodiscard]] reverse_iterator rbegin() {
      return m_data.rbegin();
    }
    [[nodiscard]] reverse_iterator rend() {
      return m_data.rend();
    }

    iterator find(int id) {
      return m_data.find(id);
    }
    [[nodiscard]] const_iterator find(int id) const {
      return m_data.find(id);
    }

    template<class Key>
    iterator find() {
      return m_data.find(type_id::of<Key>());
    }
    template<class Key>
    [[nodiscard]] const_iterator find() const {
      return m_data.find(type_id::of<Key>());
    }

    Tp & get(int id) {
      return m_data[id];
    }
    template<class Key>
    Tp & get() {
      return get(type_id::of<Key>());
    }
    void put(int id, Tp && value) {
      m_data.emplace(id, std::forward<Tp>(value));
    }
    template<class Key>
    void put(Tp && value) {
      put(type_id::of<Key>(), std::forward<Tp>(value));
    }
  };
}
