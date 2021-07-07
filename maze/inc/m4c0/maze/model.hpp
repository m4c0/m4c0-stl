#pragma once

#include <array>
#include <stdexcept>

namespace m4c0::maze::model {
  template<typename Room, typename Data>
  class wall {
    using room_t = Room;
    room_t * m_room {};

  public:
    constexpr wall() = default;
    explicit wall(room_t * r) : m_room(r) {
    }

    [[nodiscard]] explicit constexpr operator bool() const {
      return m_room != nullptr;
    }

    [[nodiscard]] constexpr const auto * room() const {
      return m_room;
    }
  };
  template<typename Data, unsigned Adjacency, typename WallData>
  class room {
    using self_t = room<Data, Adjacency, WallData>;
    using wall_t = wall<self_t, WallData>;

    std::array<wall_t, Adjacency> m_adj {};
    bool m_has_degree { false };
    Data m_data {};

  public:
    room() = default;
    ~room() = default;
    room(const room &) = delete;
    room(room &&) = delete;
    room & operator=(const room &) = delete;
    room & operator=(room &&) = delete;

    [[nodiscard]] const auto & operator[](unsigned index) const {
      return m_adj.at(index);
    }
    [[nodiscard]] explicit constexpr operator bool() const {
      return m_has_degree;
    }

    [[nodiscard]] Data & data() {
      return m_data;
    }
    [[nodiscard]] const Data & data() const {
      return m_data;
    }

    void add_adjancency(self_t * t) {
      for (auto & adj : m_adj) {
        if (!adj) {
          adj = wall_t { t };
          m_has_degree = true;
          return;
        }
      }
      throw std::runtime_error("Maze graph overflow");
    }

    template<class Fn>
    void visit_adjacents(Fn fn) const {
      for (const auto & w : m_adj) {
        if (w) fn(w.room());
      }
    }
  };
  template<typename Room, unsigned RoomCount>
  class graph {
    std::array<Room, RoomCount> m_rooms {};

  public:
    [[nodiscard]] const auto & operator[](unsigned index) const {
      return m_rooms.at(index);
    }
    [[nodiscard]] auto & operator[](unsigned index) {
      return m_rooms.at(index);
    }

    void link(unsigned from, unsigned to) {
      m_rooms.at(from).add_adjancency(&m_rooms.at(to));
    }
    void double_link(unsigned from, unsigned to) {
      link(from, to);
      link(to, from);
    }

    template<class Fn>
    void visit_rooms(Fn fn) const {
      for (const auto & room : m_rooms) {
        if (room) fn(&room);
      }
    }
    template<class Fn>
    void visit_walls(Fn fn) const {
      visit_rooms([&](const auto * r) {
        r->visit_adjacents([&](const auto * s) {
          fn(r, s);
        });
      });
    }
  };
}
