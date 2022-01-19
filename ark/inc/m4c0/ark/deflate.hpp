#pragma once

#include "m4c0/ark/bitstream.hpp"
#include "m4c0/ark/deflate.buffer.hpp"
#include "m4c0/ark/deflate.details.hpp"
#include "m4c0/ark/deflate.symbols.hpp"
#include "m4c0/io/reader.hpp"

#include <variant>

namespace m4c0::ark::deflate {
  class reader : public io::reader {
    bit_stream * m_bits;
    symbols::huff_tables m_tables;
    buffer m_buffer {};
    bool m_finished {};

  public:
    constexpr explicit reader(bit_stream * bits) : m_bits { bits } {
      auto fmt = details::read_hc_format(bits);
      auto lens = details::read_hclens(bits, fmt);
      auto hlit_hdist = details::read_hlit_hdist(fmt, lens, bits);
      m_tables = symbols::create_tables(hlit_hdist, fmt.hlit);
    }

    [[nodiscard]] constexpr bool eof() const override {
      return m_bits->eof() || m_finished;
    }
    [[nodiscard]] constexpr bool seekg(int /*pos*/, io::seek_mode /*mode*/) override {
      return false;
    }
    [[nodiscard]] constexpr unsigned tellg() const override {
      return 0;
    }

    [[nodiscard]] constexpr bool read(uint8_t * buffer, unsigned len) override {
      for (unsigned i = 0; i < len; i++) {
        const auto r = read_u8();
        if (!r) return false;
        buffer[i] = *r; // NOLINT
      }
      return true;
    }
    [[nodiscard]] bool read(void * buffer, unsigned len) override {
      return read(static_cast<uint8_t *>(buffer), len);
    }

    [[nodiscard]] constexpr std::optional<uint8_t> read_u8() override {
      if (m_buffer.empty()) {
        auto sym = symbols::read_next_symbol(m_tables, m_bits);
        if (!std::visit(m_buffer, sym)) {
          m_finished = true;
          return {};
        }
      }
      return { m_buffer.read() };
    }

    [[nodiscard]] constexpr std::optional<uint16_t> read_u16() override {
      constexpr const auto bits_per_byte = 8U;

      const auto a = read_u8();
      if (!a) return {};
      const auto b = read_u8();
      if (!b) return {};

      return { (static_cast<unsigned>(*a) << bits_per_byte) | *b };
    }
    [[nodiscard]] constexpr std::optional<uint32_t> read_u32() override {
      constexpr const auto bits_per_word = 16U;

      const auto a = read_u16();
      if (!a) return {};
      const auto b = read_u16();
      if (!b) return {};

      return { (static_cast<unsigned>(*a) << bits_per_word) | *b };
    }
  };
}
