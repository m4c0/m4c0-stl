#pragma once

#include "m4c0/ce_map.hpp"
#include "m4c0/io/reader.hpp"
#include "m4c0/io/subreader.hpp"
#include "m4c0/log.hpp"
#include "m4c0/riff/types.hpp"

#include <cstdint>
#include <type_traits>
#include <unordered_map>

namespace m4c0::riff {
  static constexpr bool warn(const char * msg) {
    if (!std::is_constant_evaluated()) {
      m4c0::log::warning(msg);
    }
    return false;
  }

  template<class CbTp, auto N, bool SucceedOnUnknown = true>
  class chunk_parser : public ce_map<fourcc_t, bool (CbTp::*)(io::reader *), N> {
    using callback_t = bool (CbTp ::*)(io::reader *);
    using parent_t = ce_map<fourcc_t, callback_t, N>;

  public:
    using pair_t = typename parent_t::pair_t;

    constexpr chunk_parser(std::initializer_list<pair_t> args) : parent_t(args) {
    }

    constexpr bool parse(io::reader * r, CbTp * cb) const {
      auto fourcc = r->read_u32();
      if (!fourcc) return warn("Failed to read chunk type");

      auto length = r->read_u32();
      if (!length) return warn("Failed to read chunk length");

      auto m = parent_t::get_or_else(*fourcc, nullptr);
      if (m == nullptr) return SucceedOnUnknown ? true : warn("Unknown chunk type found");

      auto start = r->tellg();
      auto end = start + (*length + 1U & ~1U);
      if (!r->seekg(end)) return warn("Found truncated or misaligned chunk");

      auto sr = io::subreader::seek_and_create(r, start, *length);
      if (!sr) return warn("Failure rewinding stream");

      return (cb->*m)(&sr.value()) && r->seekg(end);
    }
  };
  template<class CbTp, auto N>
  class riff_parser {
    using data_cp_t = chunk_parser<CbTp, N, true>;

    class hdr_cb {
      fourcc_t m_expected;
      CbTp * m_cb;
      const data_cp_t * m_map;

    public:
      explicit constexpr hdr_cb(fourcc_t exp, CbTp * cb, const data_cp_t * map)
        : m_expected(exp)
        , m_cb(cb)
        , m_map(map) {
      }
      constexpr bool success(io::reader * r) { // NOLINT
        auto type = r->read_u32();
        if (!type) return warn("Failed to read file type in chunk list");
        if (*type != m_expected) return warn("File is not an appropriate RIFF");

        while (!r->eof()) {
          if (!m_map->parse(r, m_cb)) return warn("Failed to parse chunk");
        }
        return true;
      }
    };

    chunk_parser<hdr_cb, 1, false> m_hdr_parser { { 'FFIR', &hdr_cb::success } };
    data_cp_t m_data_parser;
    fourcc_t m_expected;

  public:
    explicit riff_parser(fourcc_t expected, std::initializer_list<typename data_cp_t::pair_t> args)
      : m_expected(expected)
      , m_data_parser(args) {
    }

    [[nodiscard]] constexpr bool parse(io::reader * r, CbTp * cb) const {
      hdr_cb hdrcb { m_expected, cb, &m_data_parser };
      return m_hdr_parser.parse(r, &hdrcb);
    }
  };
}
