#include "m4c0/ark/zip.cdir.hpp"
#include "m4c0/ark/zip.common.hpp"

#include <algorithm>
#include <string_view>

static constexpr auto cd_data = m4c0::io::ce_reader {
  "\x50\x4b\x01\x02"                 // magic
  "\x1e\x03\x14\x00"                 // version (by + needed)
  "\x00\x00\x08\x00"                 // flags + method
  "\xb7\x98\x2d\x54"                 // modification time + date
  "\xba\x06\x4c\xba"                 // crc32
  "\x80\x01\x00\x00\x0e\x03\x00\x00" // compressed + uncompressed sizes
  "\x0c\x00\x18\x00\x00\x00"         // sizes (file, extra, comment)
  "\x00\x00\x01\x00\x00\x00\xa4\x81" // disk + attrs
  "\x42\x00\x00\x00"                 // offset

  "\x7a\x69\x70\x2e\x65\x6f\x63\x64\x2e\x63\x70\x70" // filename

  // extra
  "\x55\x54\x05\x00\x03\x0a\x78\xe0\x61\x75\x78\x0b\x00\x01\x04\xf6\x01\x00\x00\x04\x14\x00\x00\x00"
};

using namespace m4c0::ark::zip;

static_assert([] {
  constexpr const auto comp_size = 0x180;
  constexpr const auto uncomp_size = 0x030e;
  constexpr const auto crc = 0xba4c06baU;
  constexpr const auto offset = 0x42;
  constexpr const auto extra_size = 0x18;
  constexpr const std::string_view filename { "zip.eocd.cpp" };

  auto r = cd_data;
  auto cd = read_cd(&r);
  if (cd.compressed_size != comp_size) return false;
  if (cd.uncompressed_size != uncomp_size) return false;
  if (cd.crc != crc) return false;
  if (cd.offset != offset) return false;
  if (cd.filename.size() != filename.size()) return false;
  if (cd.extra.size() != extra_size) return false;
  if (!filename_matches(cd, filename)) return false;
  return r.eof();
}());
