#include "m4c0/ark/bitstream.hpp"
#include "m4c0/io/ce_reader.hpp"

using namespace m4c0::ark;

static constexpr const m4c0::io::ce_reader data { 0x8d, 0x52, 0x4d };

static_assert([] {
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
// Skip nothing from beginning
static_assert([] {
  auto r = data;
  bit_stream b { &r };
  b.skip<0>();
  return b.next<1>() == 1;
}());
// Skip nothing from somewhere
static_assert([] {
  auto r = data;
  bit_stream b { &r };
  if (b.next<1>() != 1) return false;
  b.skip<2>();
  return b.next<5>() == 17; // NOLINT
}());
// Skip from beginning
static_assert([] {
  auto r = data;
  bit_stream b { &r };
  b.skip<3>();
  return b.next<5>() == 17; // NOLINT
}());
static_assert([] {
  constexpr const m4c0::io::ce_reader data { 0x8d, 0x52, 0x4d };
  constexpr const auto bits_to_skip = 1 + 2 + 5 + 5 + 4;
  auto r = data;
  bit_stream b { &r };
  b.skip<bits_to_skip>();
  return b.next<3>() == 6 && b.next<3>() == 4; // NOLINT
}());
