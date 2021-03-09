#include "m4c0/maze/model.hpp"
#include "m4c0/test.hpp"

#include <vector>

using namespace m4c0::maze::model;
using graph_1_2 = graph<room<1>, 2>;
using graph_3_3 = graph<room<3>, 3>;
using graph_1_5 = graph<room<1>, 5>; // NOLINT

class pair {
  unsigned a;
  unsigned b;

public:
  pair(unsigned a, unsigned b) : a(a), b(b) {
  }

  [[nodiscard]] constexpr bool operator==(const pair & o) const noexcept {
    return o.a == a && o.b == b;
  }

  void dump(std::ostream & o) const {
    o << "(" << a << ", " << b << ")";
  }
};
std::ostream & operator<<(std::ostream & o, const pair & p) {
  p.dump(o);
  return o;
}

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
      apt.link(0, 1);
      apt.link(1, 2);
      apt.link(2, 3);
      apt.link(4, 3);

      it("can iterate rooms", [&] {
        std::vector<const room<1> *> visited {};
        apt.visit_rooms([&](const auto * r) {
          AssertThat(r, Is().Not().EqualTo(&apt[3]));
          visited.push_back(r);
        });

        AssertThat(visited, Is().OfLength(4));
        for (int i = 0; i <= 4; ++i) {
          if (i == 3) continue;
          AssertThat(visited, Contains(&apt[i]));
        }
      });
      it("can iterate walls", [&] {
        std::vector<pair> visited {};
        apt.visit_walls([&](const auto * from, const auto * to) {
          visited.emplace_back(from - &apt[0], to - &apt[0]);
        });

        AssertThat(visited, Is().OfLength(4));
        AssertThat(visited, Contains(pair { 0, 1 }));
        AssertThat(visited, Contains(pair { 1, 2 }));
        AssertThat(visited, Contains(pair { 2, 3 }));
        AssertThat(visited, Contains(pair { 4, 3 }));
      });
    });
  });
});
