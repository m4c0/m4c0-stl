#pragma once

#include "m4c0/io/writer.hpp"

#include <ostream>

namespace m4c0::io {
  class ostr_writer : public writer {
    std::ostream & m_os;

  public:
    explicit constexpr ostr_writer(std::ostream & os) : m_os(os) {
    }

    void write(const void * data, unsigned len) override {
      m_os.write(static_cast<const char *>(data), len);
    }

    void write_u8(std::uint8_t data) override {
      write(&data, sizeof(data));
    }
    void write_u32(std::uint32_t data) override {
      write(&data, sizeof(data));
    }

    void seekp(unsigned pos) override {
      m_os.seekp(pos);
    }
    unsigned tellp() override {
      return m_os.tellp();
    }
  };
}
