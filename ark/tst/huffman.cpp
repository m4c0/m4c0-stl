#include "m4c0/ark/bitstream.hpp"
#include "m4c0/ark/huffman.hpp"
#include "m4c0/io/ce_reader.hpp"

#include <algorithm>

using namespace m4c0::ark::huffman;

// Checks huffman table construction
static_assert([] {
  constexpr const auto expected_counts = std::array { 0, 0, 1, 5, 2 };
  constexpr const auto expected_symbols = std::array<unsigned, 8> { 5, 0, 1, 2, 3, 4, 6, 7 };

  const auto hfc = create_huffman_codes(std::array<unsigned, 8> { 3, 3, 3, 3, 3, 2, 4, 4 });
  if (!std::equal(hfc.counts.begin(), hfc.counts.end(), expected_counts.begin(), expected_counts.end())) return false;
  return hfc.indexes == expected_symbols;
}());

// Checks symbol lookup
// 0 F 00
// 1 A 010
// 2 B 011
// 3 C 100
// 4 D 101
// 5 E 110
// 6 G 1110
// 7 H 1111
static_assert([] {
  const auto hfc = create_huffman_codes(std::array<unsigned, 8> { 3, 3, 3, 3, 3, 2, 4, 4 });
  auto r = m4c0::io::ce_reader { 0b11100100, 0b01111011 }; // NOLINT
  m4c0::ark::bit_stream b { &r };

  constexpr const auto expected_result = std::array { 5, 2, 7, 3, 6 };
  for (auto er : expected_result) {
    if (decode_huffman(hfc, &b) != er) return false;
  }
  return true;
}());
