#pragma once

#include "m4c0/io/reader.hpp"

#include <array>

namespace m4c0::io {
  template<auto N>
  class ce_reader : public reader {
    std::array<uint8_t, N> m_data;
    unsigned m_pos {};

  public:
    template<typename... Tp>
    constexpr explicit ce_reader(Tp... data) : m_data { static_cast<uint8_t>(data)... } {
    }
    constexpr explicit ce_reader(const char (&data)[N + 1]) { // NOLINT
      std::copy(data, data + N, std::begin(m_data));
    }

    [[nodiscard]] constexpr bool read(void * /*buffer*/, unsigned /*len*/) override {
      return false;
    }
    [[nodiscard]] constexpr std::optional<uint8_t> read_u8() override {
      if (m_pos == N) return {};
      return m_data.at(m_pos++);
    }
    [[nodiscard]] constexpr std::optional<uint32_t> read_u32() override {
      if (m_pos + sizeof(uint32_t) > N) return {};

      constexpr const auto u8_bitsize = 8U;
      constexpr const auto u16_bitsize = 16U;

      unsigned d = *read_u8();
      unsigned c = *read_u8();
      unsigned cd = (c << u8_bitsize) | d;

      unsigned b = *read_u8();
      unsigned a = *read_u8();
      unsigned ab = (a << u8_bitsize) | b;

      return (ab << u16_bitsize) | cd;
    }
    [[nodiscard]] constexpr bool eof() override {
      return false;
    }
    [[nodiscard]] constexpr bool seekg(unsigned pos) override {
      m_pos += pos;
      return m_pos < N;
    }
    [[nodiscard]] constexpr unsigned tellg() override {
      return m_pos;
    }
  };
  template<typename... Tp>
  ce_reader(Tp...) -> ce_reader<sizeof...(Tp)>;
  template<auto N>
  ce_reader(const char (&)[N]) -> ce_reader<N - 1>; // NOLINT
}
