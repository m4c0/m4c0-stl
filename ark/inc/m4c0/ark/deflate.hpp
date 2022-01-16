#pragma once

#include "m4c0/ark/bitstream.hpp"
#include "m4c0/containers/unique_array.hpp"

#include <algorithm>
#include <array>
#include <exception>

namespace m4c0::ark::deflate {
  // Magic constants gallore - it should follow this RFC:
  // https://datatracker.ietf.org/doc/html/rfc1951
  // Note: PKZIP's "APPNOTE" does not match these

  static constexpr const auto hlit_count_bits = 5;
  static constexpr const auto hdist_count_bits = 5;
  static constexpr const auto hclen_count_bits = 4;

  static constexpr const auto hlit_min = 257;
  static constexpr const auto hdist_min = 1;
  static constexpr const auto hclen_min = 4;

  static constexpr const auto max_code_lengths = 19;
  static constexpr const auto hclen_order =
      std::array { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
  static_assert(hclen_order.size() == max_code_lengths);

  static constexpr const auto hclen_bits = 3U;

  struct dynamic_huffman_format {
    unsigned hlit;
    unsigned hdist;
    unsigned hclen;
  };

  [[nodiscard]] static constexpr auto read_hc_format(bit_stream * bits) {
    dynamic_huffman_format res {};
    res.hlit = bits->next<hlit_count_bits>() + hlit_min;
    res.hdist = bits->next<hdist_count_bits>() + hdist_min;
    res.hclen = bits->next<hclen_count_bits>() + hclen_min;
    return res;
  }

  [[nodiscard]] static constexpr auto read_hclens(bit_stream * bits, const dynamic_huffman_format & fmt) {
    std::array<unsigned, max_code_lengths> res {};
    for (int i = 0; i < fmt.hclen; i++) {
      res.at(hclen_order.at(i)) = bits->next<hclen_bits>();
    }
    return res;
  }
}
