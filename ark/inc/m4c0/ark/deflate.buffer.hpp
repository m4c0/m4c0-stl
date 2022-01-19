#pragma once

#include "m4c0/ark/deflate.symbols.hpp"

#include <array>

namespace m4c0::ark::deflate {
  class buffer {
    static constexpr const auto buf_size = 32768;

    std::array<uint8_t, buf_size> m_buf {};
    unsigned m_rd {};
    unsigned m_wr {};

    [[nodiscard]] static constexpr auto wrap(unsigned n, unsigned d) noexcept {
      return (n + d) % buf_size;
    }
    constexpr void put(uint8_t c) noexcept {
      m_buf.at(m_wr) = c;
      m_wr = wrap(m_wr, 1);
    }

  public:
    [[nodiscard]] constexpr bool empty() const noexcept {
      return m_rd == m_wr;
    }
    [[nodiscard]] constexpr uint8_t read() noexcept {
      auto p = m_rd;
      m_rd = wrap(m_rd, 1);
      return m_buf.at(p);
    }

    constexpr bool operator()(symbols::raw r) noexcept {
      put(r.c);
      return true;
    }
    constexpr bool operator()(symbols::repeat r) noexcept {
      for (unsigned i = 0; i < r.len; i++) {
        put(m_buf.at(wrap(m_wr, -r.dist)));
      }
      m_rd = wrap(m_wr, -r.len);
      return true;
    }
    constexpr bool operator()(symbols::end /**/) noexcept {
      return false;
    }
  };
}
