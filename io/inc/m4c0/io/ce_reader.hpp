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
      std::copy(data, data + N, m_data.begin());
    }

    [[nodiscard]] constexpr bool read(void * /*buffer*/, unsigned /*len*/) override {
      return false;
    }
    [[nodiscard]] constexpr std::optional<uint8_t> read_u8() override {
      if (eof()) return {};
      return m_data.at(m_pos++);
    }
    [[nodiscard]] constexpr std::optional<uint16_t> read_u16() override {
      if (m_pos + sizeof(uint16_t) > N) return {};

      constexpr const auto u8_bitsize = 8U;

      unsigned b = *read_u8();
      unsigned a = *read_u8();
      return (a << u8_bitsize) | b;
    }
    [[nodiscard]] constexpr std::optional<uint32_t> read_u32() override {
      if (m_pos + sizeof(uint32_t) > N) return {};

      constexpr const auto u16_bitsize = 16U;

      unsigned b = *read_u16();
      unsigned a = *read_u16();
      return (a << u16_bitsize) | b;
    }
    [[nodiscard]] constexpr bool eof() override {
      return m_pos >= N;
    }
    [[nodiscard]] constexpr bool seekg(unsigned pos) override {
      if (pos < 0) return false;
      if (pos > N) return false;
      m_pos = pos;
      return true;
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
