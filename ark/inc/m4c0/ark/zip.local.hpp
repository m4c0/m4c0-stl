#pragma once

#include "m4c0/ark/zip.common.hpp"
#include "m4c0/io/reader.hpp"

namespace m4c0::ark::zip::details {
  static constexpr auto ld_unwrap(auto v) {
    return unwrap<truncated_local_directory>(v);
  };
  static constexpr auto ld_match_u16(auto r, auto v) {
    if (v != ld_unwrap(r->read_u16())) throw local_directory_mismatch {};
  };
  static constexpr auto ld_match_u32(auto r, auto v) {
    if (v != ld_unwrap(r->read_u32())) throw local_directory_mismatch {};
  };
}
namespace m4c0::ark::zip {
  [[nodiscard]] static constexpr auto read_local(io::reader * r, const cdir_entry & cdir) {

    if (!r->seekg(cdir.offset)) throw invalid_file_offset {};

    constexpr const auto local_magic = 0x04034b50U; // PK\3\4
    if (details::ld_unwrap(r->read_u32()) != local_magic) {
      throw invalid_local_directory {};
    }
    if (details::ld_unwrap(r->read_u16()) > maximum_supported_version) {
      throw unsupported_zip_version {};
    }

    details::ld_match_u16(r, cdir.flags);
    details::ld_match_u16(r, cdir.method);

    auto file_mod_time = details::ld_unwrap(r->read_u16());
    auto file_mod_date = details::ld_unwrap(r->read_u16());

    details::ld_match_u32(r, cdir.crc);
    details::ld_match_u32(r, cdir.compressed_size);
    details::ld_match_u32(r, cdir.uncompressed_size);

    auto filename_len = details::ld_unwrap(r->read_u16());
    auto extra_len = details::ld_unwrap(r->read_u16());

    if (!r->seekg(filename_len + extra_len, io::seek_mode::current)) {
      throw truncated_local_directory {};
    }
  }
}
