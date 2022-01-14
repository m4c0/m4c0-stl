#pragma once

#include "m4c0/ark/zip.cdir.hpp"
#include "m4c0/ark/zip.eocd.hpp"
#include "m4c0/io/subreader.hpp"

namespace m4c0::ark::zip {
  class zip_iterator {
    io::subreader m_reader;

    static constexpr auto subreader(io::reader * r) {
      auto eocd = read_eocd(r);
      return unwrap<truncated_central_directory>(m4c0::io::subreader::seek_and_create(r, eocd.offset, eocd.size));
    }

  public:
    constexpr explicit zip_iterator(io::reader * r) : m_reader { subreader(r) } {
    }

    [[nodiscard]] constexpr explicit operator bool() const noexcept {
      return !m_reader.eof();
    }

    [[nodiscard]] constexpr auto next() {
      return read_cd(&m_reader);
    }

    [[nodiscard]] constexpr cdir_entry find(std::string_view filename) {
      if (!m_reader.seekg(0)) return {};

      while (*this) {
        auto cd = next();
        if (filename_matches(cd, filename)) {
          return cd;
        }
      }

      return {};
    }
  };
}
