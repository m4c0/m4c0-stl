#include "m4c0/ark/bitstream.hpp"
#include "m4c0/io/ce_reader.hpp"

using namespace m4c0::ark;

static_assert([] {
  constexpr const m4c0::io::ce_reader data { 0x8d, 0x52, 0x4d };
  auto r = data;
  bit_stream b { &r };
  if (b.next<1>() != 1) return false;
  if (b.next<2>() != 0b10) return false; // NOLINT
  if (b.next<5>() != 17) return false;   // NOLINT
  if (b.next<5>() != 18) return false;   // NOLINT
  if (b.next<4>() != 10) return false;   // NOLINT
  if (b.next<3>() != 6) return false;    // NOLINT
  if (b.next<3>() != 4) return false;    // NOLINT
  return true;
}());
