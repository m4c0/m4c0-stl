#pragma once

#include "m4c0/riff/reader.hpp"

#include <fstream>

namespace m4c0::riff {
  class fs_reader : public reader {
    std::ifstream & m_ifs;

  public:
    explicit constexpr fs_reader(std::ifstream & ifs) : m_ifs(ifs) {
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
