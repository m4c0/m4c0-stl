#pragma once

#include "m4c0/ark/zip.common.hpp"
#include "m4c0/io/ce_reader.hpp"

namespace m4c0::ark::zip {
  static constexpr const uint32_t eocd_magic_number = 0x06054b50; // PK\5\6

  static constexpr void find_eocd_start(io::reader * r) {
    constexpr const auto eocd_len = 22;
    if (!r->seekg(eocd_len, io::reader::seek_mode::end)) {
      throw missing_eocd_error {};
    }

    constexpr const int sizeof_u32 = sizeof(uint32_t);
    while (r->read_u32() != eocd_magic_number) {
      if (!r->seekg(-sizeof_u32 - 1, io::reader::seek_mode::current)) {
        throw missing_eocd_error {};
      }
    }
  }

  [[nodiscard]] static constexpr auto read_eocd(io::reader * r) {
    find_eocd_start(r);

    constexpr const uint16_t zip64_magic = 0xFFFF;
    auto disk_no = unwrap<truncated_eocd_error>(r->read_u16());
    if (disk_no == zip64_magic) throw zip64_is_unsupported {};
    if (disk_no != 0) throw multidisk_is_unsupported {};

    auto cdir_disk = unwrap<truncated_eocd_error>(r->read_u16());
    if (cdir_disk != 0) throw multidisk_is_unsupported {};

    auto cdir_count_disk = unwrap<truncated_eocd_error>(r->read_u16());
    auto cdir_total_count = unwrap<truncated_eocd_error>(r->read_u16());
    if (cdir_count_disk != cdir_total_count) throw multidisk_is_unsupported {};

    auto cdir_size = unwrap<truncated_eocd_error>(r->read_u32());
    auto cdir_offset = unwrap<truncated_eocd_error>(r->read_u32());

    return cdir_meta {
      .count = cdir_total_count,
      .size = cdir_size,
      .offset = cdir_offset,
    };
  }
}
