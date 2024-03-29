#pragma once

#include "m4c0/io/reader.hpp"

#include <cassert>
#include <exception>

namespace m4c0::ark {
  struct truncated_stream : std::exception {};

  class bit_stream {
    static constexpr const auto max_bits_at_once = 8;
    static constexpr const auto bits_per_byte = 8U;

    io::reader * m_reader;

    unsigned m_rem {};
    unsigned m_buf {};

  public:
    explicit constexpr bit_stream(io::reader * r) : m_reader { r } {
    }

    [[nodiscard]] constexpr auto next(unsigned n) {
      assert(n <= max_bits_at_once);

      if (m_rem < n) {
        auto next = m_reader->read_u8();
        if (!next) throw truncated_stream {};
        m_buf = m_buf + (*next << m_rem);
        m_rem += bits_per_byte;
      }

      auto res = m_buf & ((1U << n) - 1U);
      m_rem -= n;
      m_buf >>= n;
      return res;
    }

    template<size_t N>
    requires(N <= max_bits_at_once) [[nodiscard]] constexpr auto next() {
      if (m_rem < N) {
        auto next = m_reader->read_u8();
        if (!next) throw truncated_stream {};
        m_buf = m_buf + (*next << m_rem);
        m_rem += bits_per_byte;
      }

      auto res = m_buf & ((1U << N) - 1U);
      m_rem -= N;
      m_buf >>= N;
      return res;
    }

    template<size_t N>
    constexpr void skip() {
      auto rem = N;
      while (rem >= max_bits_at_once) {
        auto r = next<max_bits_at_once>();
        rem -= max_bits_at_once;
      }
      auto r = next<N % max_bits_at_once>();
    }

    [[nodiscard]] constexpr auto eof() const noexcept {
      return m_reader->eof() && m_rem == 0;
    }
  };

  template<typename Reader>
  class ce_bit_stream : public bit_stream {
    Reader m_real_reader;

  public:
    explicit constexpr ce_bit_stream(Reader r) : bit_stream { &m_real_reader }, m_real_reader { r } {};
  };
}
