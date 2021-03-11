#include "m4c0/maze/grid.hpp"
#include "m4c0/test.hpp"

using namespace m4c0::maze;

static constexpr const auto grid_width = 4;
static constexpr const auto grid_height = 3;
using grid_t = grid<grid_width, grid_height>;

go_bandit([] { // NOLINT
  describe("maze::model::grid", [] {
    it("has index and coords in-sync", [] {
      static constexpr const auto x = 4;
      static constexpr const auto y = 2;
      static constexpr const auto index = y * 7 + x;
      grid_t::position p { index };
      AssertThat(p.index(), Is().EqualTo(index));
      AssertThat(p.x(), Is().EqualTo(x));
      AssertThat(p.y(), Is().EqualTo(y));
    });
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

      model.visit_grid([&](auto pos) {
        result.at(pos.index()) = '*';
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
