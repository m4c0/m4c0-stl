#include "m4c0/maze/model.hpp"
#include "m4c0/test.hpp"

#include <vector>

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
    it("can iterate over rooms", [] {
      static constexpr const auto count = 5;
      using room = room<1>;
      graph<room, count> apt {};
      apt.link(0, 1);
      apt.link(1, 2);
      apt.link(2, 3);
      apt.link(4, 3);

      std::vector<const room *> visited {};
      apt.visit_rooms([&](const auto * r) {
        AssertThat(r, Is().Not().EqualTo(&apt[3]));
        visited.push_back(r);
      });

      AssertThat(visited, Is().OfLength(count - 1));
      for (int i = 0; i < count; i++) {
        if (i == 3) continue;
        AssertThat(visited, Contains(&apt[i]));
      }
    });
  });
});
