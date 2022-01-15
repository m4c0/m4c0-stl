#pragma once

#include "m4c0/ark/bitstream.hpp"
#include "m4c0/containers/unique_array.hpp"

#include <algorithm>
#include <array>

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
  // section 3.2.2 of RFC
  template<auto MaxCodes>
  [[nodiscard]] static constexpr auto codes_for_alphabet(const std::array<unsigned, MaxCodes> & lengths) {
    const auto max_bits = *std::max_element(lengths.begin(), lengths.end());
    containers::unique_array<unsigned> bl_count { max_bits + 1 };
    for (auto & e : bl_count) {
      e = 0;
    }

    // step 1
    for (auto len : lengths) {
      bl_count.at(len)++;
    }

    // step 2
    containers::unique_array<unsigned> next_code { max_bits + 1 };
    auto code = 0U;
    bl_count[0] = 0;
    for (auto bits = 1; bits <= max_bits; bits++) {
      code = (code + bl_count.at(bits - 1)) << 1U;
      next_code.at(bits) = code;
    }

    // step 3
    std::array<unsigned, MaxCodes> codes {};
    for (auto n = 0; n < MaxCodes; n++) {
      auto len = lengths.at(n);
      if (len != 0) {
        codes.at(n) = next_code.at(len);
        next_code.at(len)++;
      }
    }
    return codes;
  }
}
