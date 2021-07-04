#pragma once

#include "m4c0/riff/reader.hpp"

namespace m4c0::riff {
  class subreader : public reader {
    reader * m_o;
    unsigned m_start;
    unsigned m_len;

  public:
    constexpr subreader(reader * o, unsigned start, unsigned len) : m_o(o), m_start(start), m_len(len) {
    }

    [[nodiscard]] bool eof() override {
      return tellg() >= m_len;
    }
    [[nodiscard]] bool read(void * buffer, unsigned len) override {
      if (m_o->tellg() + len >= m_start + m_len) return false;
      return m_o->read(buffer, len);
    }
    [[nodiscard]] bool seekg(unsigned pos) override {
      if (pos < 0) return false;
      if (pos > m_len) return false;
      return m_o->seekg(m_start + pos);
    }
    [[nodiscard]] unsigned tellg() override {
      return m_o->tellg() - m_start;
    }
  };
}
