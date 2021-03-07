#include "m4c0/test.hpp"

#include <array>
#include <stdexcept>

template<typename Room>
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
template<unsigned Adjacency>
class room {
  using self_t = room<Adjacency>;

  std::array<wall<self_t>, Adjacency> m_adj {};

public:
  [[nodiscard]] const auto & operator[](unsigned index) const {
    return m_adj.at(index);
  }

  void add_adjancency(self_t * t) {
    for (auto & adj : m_adj) {
      if (!adj) {
        adj = wall { t };
        return;
      }
    }
    throw std::runtime_error("Maze graph overflow");
  }
};
template<typename Room, unsigned RoomCount>
class graph {
  std::array<Room, RoomCount> m_rooms {};

public:
  [[nodiscard]] const auto & operator[](unsigned index) const {
    return m_rooms.at(index);
  }

  void link(unsigned from, unsigned to) {
    m_rooms.at(from).add_adjancency(&m_rooms.at(to));
  }
};

go_bandit([] { // NOLINT
  describe("maze", [] {
    it("can be build", [] {
      graph<room<3>, 3> apt {};
      apt.link(0, 2);
      apt.link(0, 1);
      apt.link(1, 2);

      AssertThat(apt[0][0].room(), Is().EqualTo(&apt[2]));
      AssertThat(apt[0][1].room(), Is().EqualTo(&apt[1]));
      AssertThat(apt[1][0].room(), Is().EqualTo(&apt[2]));
    });
  });
});
