#include "m4c0/crc32.hpp"

#include <string_view>

static constexpr auto test_crc32(std::string_view input) {
  return m4c0::crc32(input.begin(), input.end());
}

// https://github.com/froydnj/ironclad/blob/master/testing/test-vectors/crc32.testvec
static_assert(test_crc32("") == 0x00000000U);
static_assert(test_crc32("a") == 0xe8b7be43U);              // NOLINT
static_assert(test_crc32("abc") == 0x352441c2U);            // NOLINT
static_assert(test_crc32("message digest") == 0x20159d7fU); // NOLINT
