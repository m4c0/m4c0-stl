#pragma once

#include "m4c0/riff/reader.hpp"

#include <istream>

namespace m4c0::riff {
  class istr_reader : public reader {
    std::istream & m_ifs;

  public:
    explicit constexpr istr_reader(std::istream & ifs) : m_ifs(ifs) {
    }

    [[nodiscard]] bool eof() override {
      return m_ifs.eof();
    }
    [[nodiscard]] bool read(void * buffer, unsigned len) override {
      return static_cast<bool>(m_ifs.read(static_cast<char *>(buffer), len));
    }
    [[nodiscard]] bool seekg(unsigned pos) override {
      return static_cast<bool>(m_ifs.seekg(pos));
    }
    [[nodiscard]] unsigned tellg() override {
      return m_ifs.tellg();
    }
  };
}
