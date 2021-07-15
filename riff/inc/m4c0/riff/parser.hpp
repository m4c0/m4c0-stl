#pragma once

#include "m4c0/io/reader.hpp"
#include "m4c0/io/subreader.hpp"
#include "m4c0/log.hpp"
#include "m4c0/riff/types.hpp"

#include <cstdint>
#include <unordered_map>

namespace m4c0::riff {
  static bool warn(const char * msg) {
    m4c0::log::warning(msg);
    return false;
  }

  template<class CbTp>
  class callback_map {
  protected:
    using callback_t = bool (CbTp::*)(io::reader *);

    [[nodiscard]] callback_t get(fourcc_t key) const {
      auto it = m_callbacks.find(key);
      if (it == m_callbacks.end()) return nullptr;
      return it->second;
    }

  private:
    std::unordered_map<fourcc_t, callback_t> m_callbacks {};

  public:
    void emplace(fourcc_t fourcc, callback_t cb) {
      m_callbacks.emplace(fourcc, cb);
    }
  };
  template<class CbTp, bool SucceedOnUnknown = true>
  class chunk_parser : public callback_map<CbTp> {
  public:
    bool parse(io::reader * r, CbTp * cb) const {
      auto fourcc = r->read<fourcc_t>();
      if (!fourcc) return warn("Failed to read chunk type");

      auto length = r->read<uint32_t>();
      if (!length) return warn("Failed to read chunk length");

      auto m = callback_map<CbTp>::get(*fourcc);
      if (m == nullptr) return SucceedOnUnknown ? true : warn("Unknown chunk type found");

      auto start = r->tellg();
      auto end = start + (*length + 1U & ~1U);
      if (!r->seekg(end)) return warn("Found truncated or misaligned chunk");

      auto sr = io::subreader::seek_and_create(r, start, *length);
      if (!sr) return warn("Failure rewinding stream");

      return (cb->*m)(&sr.value()) && r->seekg(end);
    }
  };
  template<class CbTp>
  class riff_parser {
    class hdr_cb {
      fourcc_t m_expected;
      CbTp * m_cb;
      const chunk_parser<CbTp> * m_map;

    public:
      explicit constexpr hdr_cb(fourcc_t exp, CbTp * cb, const chunk_parser<CbTp> * map)
        : m_expected(exp)
        , m_cb(cb)
        , m_map(map) {
      }
      bool success(io::reader * r) { // NOLINT
        auto type = r->read<fourcc_t>();
        if (!type) return warn("Failed to read file type in chunk list");
        if (*type != m_expected) return warn("File is not an appropriate RIFF");

        while (!r->eof()) {
          if (!m_map->parse(r, m_cb)) return warn("Failed to parse chunk");
        }
        return true;
      }
    };

    chunk_parser<hdr_cb, false> m_hdr_parser {};
    chunk_parser<CbTp, true> m_data_parser {};
    fourcc_t m_expected;

  public:
    explicit riff_parser(fourcc_t expected) : m_expected(expected) {
      m_hdr_parser.emplace('FFIR', &hdr_cb::success);
    }

    template<class Cb>
    void emplace(fourcc_t fourcc, Cb && cb) {
      m_data_parser.emplace(fourcc, std::forward<Cb>(cb));
    }

    [[nodiscard]] bool parse(io::reader * r, CbTp * cb) const {
      hdr_cb hdrcb { m_expected, cb, &m_data_parser };
      return m_hdr_parser.parse(r, &hdrcb);
    }
  };
}
