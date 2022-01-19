#pragma once

#include "m4c0/ark/bitstream.hpp"
#include "m4c0/containers/unique_array.hpp"

#include <algorithm>
#include <array>
#include <exception>

namespace m4c0::ark::huffman {
  struct invalid_huffman_code : std::exception {};

  struct huffman_codes {
    // Counts per bit length
    containers::unique_array<unsigned> counts {};
    // Symbol per offset
    containers::unique_array<unsigned> indexes {};
  };

  // section 3.2.2 of RFC 1951 - using a variant based on ZLIB algorithms
  template<typename LengthArray>
  [[nodiscard]] static constexpr auto create_huffman_codes(const LengthArray & lengths) {
    const auto max_codes = lengths.size();
    const auto max_bits = *std::max_element(lengths.begin(), lengths.end());
    huffman_codes res;
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

    res.indexes = containers::unique_array<unsigned> { offsets.at(max_bits) + res.counts.at(max_bits) };
    for (auto n = 0; n < max_codes; n++) {
      auto len = lengths[n];
      if (len != 0) {
        res.indexes.at(offsets.at(len)) = n;
        offsets.at(len)++;
      }
    }

    return res;
  }

  [[nodiscard]] static constexpr auto decode_huffman(const huffman_codes & hc, bit_stream * bits) {
    unsigned code = 0;
    unsigned first = 0;
    unsigned index = 0;
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (const auto * it = hc.counts.begin() + 1; it != hc.counts.end(); ++it) {
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
