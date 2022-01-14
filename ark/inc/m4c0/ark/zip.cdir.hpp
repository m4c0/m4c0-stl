#pragma once

#include "m4c0/ark/zip.common.hpp"
#include "m4c0/ark/zip.eocd.hpp"

namespace m4c0::ark::zip {
  static constexpr auto read_cd(io::reader * r) {
    constexpr const auto cdir_magic = 0x02014b50;        // PK\1\2
    constexpr const auto maximum_supported_version = 20; // 2.0 - Deflate

    if (unwrap<truncated_central_directory>(r->read_u32()) != cdir_magic) {
      throw invalid_central_directory {};
    }
    unwrap<truncated_central_directory>(r->read_u16()); // Version made by
    if (unwrap<truncated_central_directory>(r->read_u16()) > maximum_supported_version) {
      throw unsupported_zip_version {};
    }

    cdir_entry result;
    result.flags = unwrap<truncated_central_directory>(r->read_u16());
    result.method = unwrap<truncated_central_directory>(r->read_u16());

    unwrap<truncated_central_directory>(r->read_u16()); // Modification time
    unwrap<truncated_central_directory>(r->read_u16()); // Modification date

    result.crc = unwrap<truncated_central_directory>(r->read_u32());
    result.compressed_size = unwrap<truncated_central_directory>(r->read_u32());
    result.uncompressed_size = unwrap<truncated_central_directory>(r->read_u32());

    auto filename_len = unwrap<truncated_central_directory>(r->read_u16());
    auto extra_len = unwrap<truncated_central_directory>(r->read_u16());
    auto comment_len = unwrap<truncated_central_directory>(r->read_u16());

    if (unwrap<truncated_central_directory>(r->read_u16()) != 0) {
      throw multidisk_is_unsupported {};
    }

    unwrap<truncated_central_directory>(r->read_u16()); // Internal file attr
    unwrap<truncated_central_directory>(r->read_u32()); // External file attr

    result.offset = unwrap<truncated_central_directory>(r->read_u32());

    result.filename = containers::unique_array<uint8_t> { filename_len };
    if (!r->read(result.filename.begin(), filename_len)) {
      throw truncated_central_directory {};
    }

    result.extra = containers::unique_array<uint8_t> { extra_len };
    if (!r->read(result.extra.begin(), extra_len)) {
      throw truncated_central_directory {};
    }

    if (!r->seekg(comment_len, io::seek_mode::current)) {
      throw truncated_central_directory {};
    }

    return result;
  }
}
