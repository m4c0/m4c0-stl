#pragma once

#include <optional>

namespace m4c0::io {
  namespace details {
    [[nodiscard]] static constexpr uint16_t flip(uint16_t u16) noexcept {
      constexpr const auto u8_bitsize = 8U;
      uint8_t a = u16;
      uint8_t b = u16 >> u8_bitsize;
      return static_cast<uint16_t>(a << u8_bitsize) | b;
    }

    [[nodiscard]] static constexpr uint32_t flip(uint32_t u32) noexcept {
      constexpr const auto u16_bitsize = 16U;
      uint16_t ab = flip(static_cast<uint16_t>(u32));
      uint16_t cd = flip(static_cast<uint16_t>(u32 >> u16_bitsize));
      return static_cast<uint32_t>(ab << u16_bitsize) | cd;
    }
    static constexpr const auto test_be = 0xaabbccddU;
    static constexpr const auto test_le = 0xddccbbaaU;
    static_assert(flip(test_be) == test_le);
  }

  enum class seek_mode { set, current, end };

  class reader {
    friend class subreader;

  public:
    [[nodiscard]] virtual bool eof() const = 0;
    [[nodiscard]] virtual bool seekg(int pos, seek_mode mode) = 0;
    [[nodiscard]] virtual unsigned tellg() const = 0;

    [[nodiscard]] constexpr bool seekg(unsigned pos) {
      return seekg(static_cast<int>(pos), seek_mode::set);
    }

    [[nodiscard]] virtual bool read(uint8_t * buffer, unsigned len) {
      return read(static_cast<void *>(buffer), len);
    }
    [[nodiscard]] virtual bool read(void * buffer, unsigned len) = 0;
    [[nodiscard]] virtual std::optional<uint8_t> read_u8() = 0;
    [[nodiscard]] virtual std::optional<uint16_t> read_u16() = 0;
    [[nodiscard]] virtual std::optional<uint32_t> read_u32() = 0;

    [[nodiscard]] constexpr std::optional<uint16_t> read_u16_be() {
      auto u16 = read_u16();
      if (!u16) return {};
      return { details::flip(*u16) };
    }
    [[nodiscard]] constexpr std::optional<uint32_t> read_u32_be() {
      auto u32 = read_u32();
      if (!u32) return {};
      return { details::flip(*u32) };
    }
  };
}
