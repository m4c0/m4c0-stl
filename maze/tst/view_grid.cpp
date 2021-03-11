#include "m4c0/maze/model.hpp"
#include "m4c0/test.hpp"

using namespace m4c0::maze::model;

template<unsigned GridW, unsigned GridH>
class grid {
  static constexpr const auto grid_width = GridW;
  static constexpr const auto grid_height = GridH;
  static constexpr const auto room_count = grid_width * grid_height;

  using room_t = room<int, 4>;

  graph<room_t, room_count> m_graph {};

public:
  static constexpr const auto array_width = grid_width * 2 - 1;
  static constexpr const auto array_size = array_width * (grid_height * 2 - 1);

  constexpr grid() {
    for (int y = 0, i = 0; y < grid_height; ++y) {
      for (int x = 0; x < grid_width; ++x, ++i) {
        m_graph[i].data() = y * array_width * 2 + x * 2;
      }
    }
  }

  void double_link(unsigned from, unsigned to) {
    m_graph.double_link(from, to);
  }

  template<typename Fn>
  void visit_grid(Fn fn) const {
    m_graph.visit_rooms([&](const room_t * r) {
      fn(r->data());
    });
    m_graph.visit_walls([&](const room_t * ra, const room_t * rb) {
      fn((ra->data() + rb->data()) / 2);
    });
  }
};

static constexpr const auto grid_width = 4;
static constexpr const auto grid_height = 3;
using grid_t = grid<grid_width, grid_height>;

go_bandit([] { // NOLINT
  describe("maze::model::grid", [] {
    it("can be visited by index", [] {
      // Expected:
      // 0*1*2 3
      //   *   *
      // 4 5 6*7
      // * * * *
      // 8*9*A B
      enum { R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, RA, RB };

      grid_t model {};
      model.double_link(R0, R1);
      model.double_link(R1, R2);
      model.double_link(R1, R5);
      model.double_link(R5, R9);
      model.double_link(R9, R8);
      model.double_link(R8, R4);
      model.double_link(R9, RA);
      model.double_link(RA, R6);
      model.double_link(R6, R7);
      model.double_link(R7, R3);
      model.double_link(R7, RB);

      std::array<char, grid_t::array_size + 1> result {};
      std::fill(std::begin(result), std::end(result), ' ');
      result[grid_t::array_size] = 0;

      model.visit_grid([&](unsigned index) {
        result.at(index) = '*';
      });

      AssertThat(
          result.data(),
          Is().EqualTo("***** *"
                       "  *   *"
                       "* * ***"
                       "* * * *"
                       "***** *"));
    });
  });
});
