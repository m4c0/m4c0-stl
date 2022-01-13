#include "m4c0/ark/zip.eocd.hpp"

// Test ZIP contains a single empty file named "file.txt"

// End-of-central-directory has an extra comment to test the reverse seek and extra padding at front
static constexpr auto eocd_data = m4c0::io::ce_reader {
  "\x50\x4b\x01\x02\x00" // pad
  "\x50\x4b\x05\x06\x00\x00\x00\x00"
  "\x01\x00\x01\x00\x4e\x00\x00\x00"
  "\x42\x00\x00\x00\x00\x03"
  "---" // pad
};

using namespace m4c0::ark::zip;

static_assert([] {
  constexpr const auto after_pk56_pos = 5 + 4; // PAD + u32

  auto r = eocd_data;
  find_eocd_start(&r);
  return r.tellg() == after_pk56_pos;
}());
static_assert([] {
  constexpr const auto cdm_size = 0x4e;
  constexpr const auto cdm_offset = 0x42;

  auto r = eocd_data;
  auto cdm = read_eocd(&r);
  return cdm.count == 1 && cdm.size == cdm_size && cdm.offset == cdm_offset;
}());

int main() {
}
