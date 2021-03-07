#include "m4c0/maze/model.hpp"
#include "m4c0/test.hpp"

using namespace m4c0::maze::model;
using graph_1_2 = graph<room<1>, 2>;
using graph_3_3 = graph<room<3>, 3>;

go_bandit([] { // NOLINT
  describe("maze::model", [] {
    it("can descibe a graph", [] {
      graph_3_3 apt {};
      apt.link(0, 2);
      apt.link(0, 1);
      apt.link(1, 2);

      AssertThat(apt[0][0].room(), Is().EqualTo(&apt[2]));
      AssertThat(apt[0][1].room(), Is().EqualTo(&apt[1]));
      AssertThat(apt[1][0].room(), Is().EqualTo(&apt[2]));
    });
    it("can single link nodes", [] {
      graph_1_2 apt {};
      apt.link(0, 1);

      AssertThat(apt[0][0].room(), Is().EqualTo(&apt[1]));
      AssertThat(apt[1][0].room(), Is().Null());
    });
    it("can double link nodes", [] {
      graph_1_2 apt {};
      apt.double_link(0, 1);

      AssertThat(apt[0][0].room(), Is().EqualTo(&apt[1]));
      AssertThat(apt[1][0].room(), Is().EqualTo(&apt[0]));
    });
  });
});
