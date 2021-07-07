#pragma once

#include "m4c0/maze/model.hpp"

namespace m4c0::maze {
  template<unsigned GridW, unsigned GridH>
  class grid {
    static constexpr const auto grid_width = GridW;
    static constexpr const auto grid_height = GridH;
    static constexpr const auto room_count = grid_width * grid_height;

    using room_t = model::room<unsigned, 4, void>;
    using graph_t = model::graph<room_t, room_count>;

    graph_t m_graph {};

  public:
    static constexpr const auto array_width = grid_width * 2 - 1;
    static constexpr const auto array_size = array_width * (grid_height * 2 - 1);

    class position {
      unsigned m_index;

    public:
      explicit constexpr position(unsigned i) : m_index(i) {
      }

      [[nodiscard]] constexpr auto index() const noexcept {
        return m_index;
      }
      [[nodiscard]] constexpr auto x() const noexcept {
        return m_index % array_width;
      }
      [[nodiscard]] constexpr auto y() const noexcept {
        return m_index / array_width;
      }
    };

    constexpr grid() {
      for (int y = 0, i = 0; y < grid_height; ++y) {
        for (int x = 0; x < grid_width; ++x, ++i) {
          m_graph[i].data() = y * array_width * 2 + x * 2;
        }
      }
    }

    // Only double link are supported for now
    void double_link(unsigned from, unsigned to) {
      m_graph.double_link(from, to);
    }

    template<typename Fn>
    void visit_grid(Fn fn) const {
      m_graph.visit_rooms([&](const room_t * r) {
        fn(position { r->data() });
      });
      m_graph.visit_walls([&](const room_t * ra, const room_t * rb) {
        fn(position { (ra->data() + rb->data()) / 2 });
      });
    }
  };
}
