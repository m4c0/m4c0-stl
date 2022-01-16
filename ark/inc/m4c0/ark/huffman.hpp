#pragma once

#include "m4c0/ark/bitstream.hpp"
#include "m4c0/containers/unique_array.hpp"

#include <algorithm>
#include <array>
#include <exception>

namespace m4c0::ark::huffman {
  struct invalid_huffman_code : std::exception {};

  template<auto MaxCodes>
  struct huffman_codes {
    // Counts per bit length
    containers::unique_array<unsigned> counts {};
    // Symbol per offset
    std::array<unsigned, MaxCodes> indexes {};
  };

  // section 3.2.2 of RFC 1951 - using a variant based on ZLIB algorithms
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
