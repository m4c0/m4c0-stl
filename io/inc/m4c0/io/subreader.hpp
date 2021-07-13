#pragma once

#include "m4c0/io/reader.hpp"

#include <optional>

namespace m4c0::io {
  class subreader : public reader {
    reader * m_o;
    unsigned m_start;
    unsigned m_len;

    constexpr subreader(reader * o, unsigned start, unsigned len) : m_o(o), m_start(start), m_len(len) {
    }

  public:
    static std::optional<subreader> seek_and_create(reader * o, unsigned start, unsigned len) {
      if (!o->seekg(start)) return {};
      return { subreader { o, start, len } };
    }

    [[nodiscard]] bool eof() override {
      return tellg() >= m_len;
    }
    [[nodiscard]] bool read(void * buffer, unsigned len) override {
      if (tellg() + len > m_len) return false;
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
