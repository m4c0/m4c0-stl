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

  template<auto MaxCodes>
  struct huffman_codes {
    // Counts per bit length
    containers::unique_array<unsigned> counts {};
    // Symbol per offset
    std::array<unsigned, MaxCodes> indexes {};
  };

  // section 3.2.2 of RFC - using a variant based on ZLIB algorithms
  template<auto MaxCodes>
  [[nodiscard]] static constexpr auto create_huffman_codes(const std::array<unsigned, MaxCodes> & lengths) {
    const auto max_bits = *std::max_element(lengths.begin(), lengths.end());
    huffman_codes<MaxCodes> res;
    res.counts = containers::unique_array<unsigned> { max_bits + 1 };
    for (auto & e : res.counts) {
      e = 0;
    }
    for (auto len : lengths) {
      res.counts.at(len)++;
    }

    containers::unique_array<unsigned> offsets { max_bits + 1 };
    offsets.at(1) = 0;
    for (auto bits = 1; bits < max_bits; bits++) {
      offsets.at(bits + 1) = offsets.at(bits) + res.counts.at(bits);
    }

    for (auto n = 0; n < MaxCodes; n++) {
      auto len = lengths.at(n);
      if (len != 0) {
        res.indexes.at(offsets.at(len)) = n;
        offsets.at(len)++;
      }
    }

    return res;
  }

  struct invalid_huffman_code : std::exception {};

  template<auto MaxCodes>
  [[nodiscard]] static constexpr auto decode_huffman(const huffman_codes<MaxCodes> & hc, bit_stream * bits) {
    unsigned code = 0;
    unsigned first = 0;
    unsigned index = 0;
    for (auto it = hc.counts.begin() + 1; it != hc.counts.end(); ++it) {
      auto count = *it;

      code |= bits->next<1>();
      if (code < first + count) {
        return hc.indexes.at(index + code - first);
      }
      index += count;
      first = (first + count) << 1U;
      code <<= 1U;
    }
    throw invalid_huffman_code {};
  }
}
