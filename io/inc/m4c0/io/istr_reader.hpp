#pragma once

#include "m4c0/io/reader.hpp"

#include <istream>

namespace m4c0::io {
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
    [[nodiscard]] std::optional<uint32_t> read_u32() override {
      uint32_t res {};
      if (read(&res, sizeof(uint32_t))) return res;
      return {};
    }
    [[nodiscard]] std::optional<uint8_t> read_u8() override {
      uint8_t res {};
      if (read(&res, sizeof(uint8_t))) return res;
      return {};
    }

    [[nodiscard]] bool seekg(unsigned pos) override {
      return static_cast<bool>(m_ifs.seekg(pos));
    }
    [[nodiscard]] unsigned tellg() override {
      return m_ifs.tellg();
    }
  };
}
