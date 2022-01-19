#include "m4c0/ark/bitstream.hpp"
#include "m4c0/ark/deflate.symbols.hpp"
#include "m4c0/ark/huffman.hpp"
#include "m4c0/io/ce_reader.hpp"

#include <variant>

using namespace m4c0::ark::deflate::symbols;

namespace m4c0::ark::deflate::symbols {
  static constexpr bool operator==(const raw & s, const raw & r) {
    return s.c == r.c;
  }
  static constexpr bool operator==(const repeat & s, const repeat & r) {
    return s.dist == r.dist && s.len == r.len;
  }
  static constexpr bool operator==(const end & /**/, const end & /**/) {
    return true;
  }

  static constexpr bool operator==(const bit_pair & s, const bit_pair & r) {
    return s.bits == r.bits && s.second == r.second;
  }
}

// More magic number fest - All straight from RFC 1951 - sec 3.2.5
static_assert(bitlen_for_code(258) == bit_pair { 0, 4 });      // NOLINT
static_assert(bitlen_for_code(280) == bit_pair { 4, 115 });    // NOLINT
static_assert(bitlen_for_code(281) == bit_pair { 5, 131 });    // NOLINT
static_assert(bitlen_for_code(285) == bit_pair { 0, 258 });    // NOLINT
static_assert(bitdist_for_code(0) == bit_pair { 0, 1 });       // NOLINT
static_assert(bitdist_for_code(2) == bit_pair { 0, 3 });       // NOLINT
static_assert(bitdist_for_code(3) == bit_pair { 0, 4 });       // NOLINT
static_assert(bitdist_for_code(4) == bit_pair { 1, 5 });       // NOLINT
static_assert(bitdist_for_code(5) == bit_pair { 1, 7 });       // NOLINT
static_assert(bitdist_for_code(6) == bit_pair { 2, 9 });       // NOLINT
static_assert(bitdist_for_code(29) == bit_pair { 13, 24577 }); // NOLINT

static constexpr auto build_huffman_codes(const auto & indexes, const auto & counts) {
  m4c0::ark::huffman::huffman_codes huff {
    .counts { counts.size() },
    .indexes { indexes.size() },
  };
  std::copy(counts.begin(), counts.end(), huff.counts.begin());
  std::copy(indexes.begin(), indexes.end(), huff.indexes.begin());
  return huff;
}
static constexpr auto build_sparse_huff() {
  // 2-bit alignment to match a half-hex and simplify the assertion
  constexpr const auto lit_indexes = std::array<unsigned, 4> { '?', 256, 270, 285 };
  constexpr const auto dist_indexes = std::array<unsigned, 4> { 2, 6 };

  constexpr const auto lit_counts = std::array<unsigned, 3> { 0, 0, lit_indexes.size() };
  constexpr const auto dist_counts = std::array<unsigned, 3> { 0, 0, dist_indexes.size() };

  return huff_tables {
    .hlist = build_huffman_codes(lit_indexes, lit_counts),
    .hdist = build_huffman_codes(dist_indexes, dist_counts),
  };
}
static constexpr auto test_read_next_symbol(uint8_t data, symbol expected) {
  auto bits = m4c0::ark::ce_bit_stream { m4c0::io::ce_reader { data } };
  auto sym = read_next_symbol(build_sparse_huff(), &bits);
  return sym == expected;
}
static_assert(test_read_next_symbol(0b00, raw { '?' }));             // NOLINT
static_assert(test_read_next_symbol(0b10, end {}));                  // NOLINT
static_assert(test_read_next_symbol(0b11100101, repeat { 24, 12 })); // NOLINT

static_assert([] {
  constexpr const auto data = std::array<unsigned, 5> { 2, 2, 2, 1, 1 };
  const auto tables = create_tables(data, 3);
  if (tables.hlist.counts[2] != 3) return false;
  if (tables.hlist.counts[1] != 0) return false;
  if (tables.hdist.counts.size() == 3) return false;
  if (tables.hdist.counts[1] != 2) return false;
  return true;
}());
