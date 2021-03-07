#include "m4c0/test.hpp"

#include <array>
#include <stdexcept>

template<typename Wall, unsigned Adjacency>
class room {
  using self_t = room<Wall, Adjacency>;

  std::array<Wall, Adjacency> m_adj {};

public:
  [[nodiscard]] const auto & operator[](unsigned index) const {
    return m_adj.at(index);
  }

  void add_adjancency(self_t * t) {
    for (auto & adj : m_adj) {
      if (!adj) {
        adj = Wall { t };
        return;
      }
    }
    throw std::runtime_error("Maze graph overflow");
  }
};

go_bandit([] { // NOLINT
  describe("maze", [] {
    it("can be build", [] {
      struct wall;
      using room = room<wall, 3>;
      class wall {
        room * m_room {};

      public:
        constexpr wall() = default;
        explicit wall(room * r) : m_room(r) {
        }

        [[nodiscard]] explicit constexpr operator bool() const {
          return m_room != nullptr;
        }

        [[nodiscard]] constexpr const auto * room() const {
          return m_room;
        }
      };

      std::array<room, 3> apt {};
      apt[0].add_adjancency(&apt[2]);
      apt[0].add_adjancency(&apt[1]);
      apt[1].add_adjancency(&apt[2]);

      AssertThat(apt[0][0].room(), Is().EqualTo(&apt[2]));
      AssertThat(apt[0][1].room(), Is().EqualTo(&apt[1]));
      AssertThat(apt[1][0].room(), Is().EqualTo(&apt[2]));
    });
  });
});
