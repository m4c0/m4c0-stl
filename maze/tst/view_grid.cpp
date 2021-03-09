#include "m4c0/maze/model.hpp"
#include "m4c0/test.hpp"

using namespace m4c0::maze::model;
static constexpr const auto room_count = 12;
static constexpr const auto grid_width = 4;
static constexpr const auto grid_height = 3;
static constexpr const auto array_width = grid_width * 2 - 1;
static constexpr const auto array_size = array_width * (grid_height * 2 - 1);

using my_room = room<int, 4>;

go_bandit([] { // NOLINT
  describe("maze::view::grid", [] {
    it("works", [] {
      // Expected:
      // 0*1*2 3
      //   *   *
      // 4 5 6*7
      // * * * *
      // 8*9*A B
      enum { R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, RA, RB };

      graph<my_room, room_count> model {};
      for (int y = 0, i = 0; y < grid_height; ++y) {
        for (int x = 0; x < grid_width; ++x, ++i) {
          model[i].data() = y * array_width * 2 + x * 2;
        }
      }

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

      std::array<char, array_size + 1> result {};
      std::fill(std::begin(result), std::end(result), ' ');
      result[array_size] = 0;

      model.visit_rooms([&](const auto * r) {
        result[r->data()] = '*';
      });
      model.visit_walls([&](const auto * ra, const auto * rb) {
        result[(ra->data() + rb->data()) / 2] = '*';
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
