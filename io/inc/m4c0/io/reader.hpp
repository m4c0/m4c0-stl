#pragma once

#include <optional>

namespace m4c0::io {
  namespace details {
    [[nodiscard]] static constexpr uint32_t flip(uint32_t u32) noexcept {
      constexpr const auto u8_bitsize = 8U;
      constexpr const auto u16_bitsize = 16U;
      uint16_t ab = u32;
      uint8_t a = ab;
      uint8_t b = ab >> u8_bitsize;
      ab = static_cast<uint16_t>(a << u8_bitsize) | b;

      uint16_t cd = u32 >> u16_bitsize;
      uint8_t c = cd;
      uint8_t d = cd >> u8_bitsize;
      cd = static_cast<uint16_t>(c << u8_bitsize) | d;

      return static_cast<uint32_t>(ab << u16_bitsize) | cd;
    }
    static constexpr const auto test_be = 0xaabbccddU;
    static constexpr const auto test_le = 0xddccbbaaU;
    static_assert(flip(test_be) == test_le);
  }

  class reader {
    friend class subreader;

  public:
    [[nodiscard]] virtual bool eof() = 0;
    [[nodiscard]] virtual bool seekg(unsigned pos) = 0;
    [[nodiscard]] virtual unsigned tellg() = 0;

    [[nodiscard]] virtual bool read(void * buffer, unsigned len) = 0;
    [[nodiscard]] virtual std::optional<uint8_t> read_u8() = 0;
    [[nodiscard]] constexpr virtual std::optional<uint32_t> read_u32() = 0;

    [[nodiscard]] constexpr std::optional<uint32_t> read_u32_be() {
      auto u32 = read_u32();
      if (!u32) return {};
      return { details::flip(*u32) };
    }
  };
}
