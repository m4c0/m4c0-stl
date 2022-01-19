#pragma once

#include "m4c0/ark/bitstream.hpp"
#include "m4c0/ark/huffman.hpp"

#include <span>
#include <variant>

namespace m4c0::ark::deflate::symbols {
  struct raw {
    uint8_t c;
  };
  struct repeat {
    unsigned len;
    unsigned dist;
  };
  struct end {};
  using symbol = std::variant<end, raw, repeat>;

  struct bit_pair {
    unsigned bits;
    unsigned second;
  };

  static constexpr const auto max_lens_code = 285;
  static constexpr const auto min_lens_code = 257;
  [[nodiscard]] static constexpr auto build_lens_arrays() noexcept {
    constexpr const auto last = max_lens_code - min_lens_code;
    std::array<unsigned, last + 1> res {};
    for (auto i = 0U; i < 4; i++) {
      res.at(i + 4) = i + 7; // NOLINT
    }
    for (auto i = 8U; i <= last - 1; i += 4) { // NOLINT
      const auto bits = (i - 4U) / 4U;
      res.at(i) = res.at(i - 4) + (2U << bits);
      res.at(i + 1) = res.at(i) + (1U << bits);
      res.at(i + 2) = res.at(i + 1) + (1U << bits);
      res.at(i + 3) = res.at(i + 2) + (1U << bits);
    }
    return res;
  }
  [[nodiscard]] static constexpr auto bitlen_for_code(unsigned code) {
    constexpr const auto last_pair = bit_pair { 0, 258 };
    if (code == max_lens_code) return last_pair;

    const auto index = code - min_lens_code;
    if (index < 4) return bit_pair { 0, index + 3 };

    constexpr const auto lens = build_lens_arrays();
    const auto bits = (index - 4U) / 4U;
    return bit_pair { bits, lens.at(index) };
  }
  [[nodiscard]] static constexpr auto build_dist_arrays() noexcept {
    constexpr const auto last = 29;
    std::array<unsigned, last + 1> res {};
    res[2] = 3;
    res[3] = 4;
    for (auto i = 4U; i <= last - 1; i += 2) {
      const auto bits = (i - 2U) / 2U;
      res.at(i) = res.at(i - 2) + (1U << bits);
      res.at(i + 1) = res.at(i) + (1U << bits);
    }
    return res;
  }
  [[nodiscard]] static constexpr auto bitdist_for_code(unsigned code) noexcept {
    constexpr const auto dists = build_dist_arrays();
    if (code < 2) return bit_pair { code, code + 1 };
    const auto bits = (code - 2U) / 2U;
    return bit_pair { bits, dists.at(code) };
  }

  struct huff_tables {
    huffman::huffman_codes hlist;
    huffman::huffman_codes hdist;
  };
  [[nodiscard]] static constexpr symbol read_next_symbol(const huff_tables & huff, bit_stream * bits) {
    constexpr const auto end_code = 256;

    const auto code = huffman::decode_huffman(huff.hlist, bits);
    if (code < end_code) return raw { static_cast<uint8_t>(code) };
    if (code == end_code) return end {};

    const auto len_bits = bitlen_for_code(code);
    const auto len = len_bits.second + bits->next(len_bits.bits);

    const auto dist_code = huffman::decode_huffman(huff.hdist, bits);
    const auto dist_bits = bitdist_for_code(dist_code);
    const auto dist = dist_bits.second + bits->next(dist_bits.bits);

    return repeat { len, dist };
  }

  template<typename LenDistBits>
  [[nodiscard]] static constexpr huff_tables create_tables(const LenDistBits & hlist_hdist, unsigned hlist_len) {
    std::span sp { hlist_hdist.begin(), hlist_hdist.end() };
    return huff_tables {
      .hlist = huffman::create_huffman_codes(sp.subspan(0, hlist_len)),
      .hdist = huffman::create_huffman_codes(sp.subspan(hlist_len)),
    };
  }
}
