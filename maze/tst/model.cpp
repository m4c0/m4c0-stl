#include "m4c0/maze/model.hpp"
#include "m4c0/test.hpp"

#include <vector>

using namespace m4c0::maze::model;
using graph_1_2 = graph<room<char, 1>, 2>;
using graph_3_3 = graph<room<char, 3>, 3>;
using graph_1_5 = graph<room<char, 1>, 5>; // NOLINT

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

    describe("iterations", [] {
      graph_1_5 apt {};
      for (int i = 0; i <= 4; ++i) {
        apt[i].data() = '0' + i;
      }
      apt.link(0, 1);
      apt.link(1, 2);
      apt.link(2, 3);
      apt.link(4, 3);

      it("can iterate rooms", [&] {
        std::vector<char> visited {};
        apt.visit_rooms([&](const auto * r) {
          visited.push_back(r->data());
        });
        visited.push_back(0);

        AssertThat(visited.data(), Is().EqualTo("0124"));
      });
      it("can iterate walls", [&] {
        std::vector<char> visited {};
        apt.visit_walls([&](const auto * from, const auto * to) {
          visited.push_back(from->data());
          visited.push_back(to->data());
        });
        visited.push_back(0);

        AssertThat(
            visited.data(),
            Is().EqualTo("01"
                         "12"
                         "23"
                         "43"));
      });
    });
  });
});
