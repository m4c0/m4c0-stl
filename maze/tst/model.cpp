#include "m4c0/maze/model.hpp"
#include "m4c0/test.hpp"

go_bandit([] { // NOLINT
  describe("maze::model", [] {
    it("can descibe a graph", [] {
      using namespace m4c0::maze::model;

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
