#pragma once

#include "m4c0/riff/types.hpp"
#include "m4c0/riff/writer.hpp"

namespace m4c0::riff {
  class riff_builder {
    class chunk_writer {
      writer * m_w;
      unsigned m_start;

    public:
      chunk_writer(writer * w, fourcc_t fourcc) : m_w(w) {
        w->write(fourcc);
        w->write(static_cast<std::uint32_t>(0));
        m_start = w->tellp();
      }
      ~chunk_writer() {
        auto end = m_w->tellp();
        if (end % 2 == 1) {
          m_w->write('\0');
        }
        std::uint32_t len = end - m_start;
        m_w->seekp(m_start - sizeof(len));
        m_w->write(len);
        m_w->seekp(end + 1U & ~1U);
      }

      chunk_writer(const chunk_writer &) = delete;
      chunk_writer(chunk_writer &&) = delete;
      chunk_writer & operator=(const chunk_writer &) = delete;
      chunk_writer & operator=(chunk_writer &&) = delete;
    };

    chunk_writer m_hdr;
    writer * m_w;

  public:
    riff_builder(writer * w, fourcc_t fourcc) : m_hdr(w, 'FFIR'), m_w(w) {
      w->write(fourcc);
    }

    template<class Tp>
    riff_builder & write(fourcc_t fourcc, Tp && data) {
      chunk_writer cw(m_w, fourcc);
      m_w->write(data);
      return *this;
    }
    riff_builder & write(fourcc_t fourcc, const void * data, unsigned len) {
      chunk_writer cw(m_w, fourcc);
      m_w->write(data, len);
      return *this;
    }
  };
}
