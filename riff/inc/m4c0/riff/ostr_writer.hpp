#pragma once

#include "m4c0/riff/writer.hpp"

#include <ostream>

namespace m4c0::riff {
  class ostr_writer : public writer {
    std::ostream & m_os;

  public:
    explicit constexpr ostr_writer(std::ostream & os) : m_os(os) {
    }

    void write(const void * buffer, unsigned len) override {
      m_os.write(static_cast<const char *>(buffer), len);
    }
    void seekp(unsigned pos) override {
      m_os.seekp(pos);
    }
    unsigned tellp() override {
      return m_os.tellp();
    }
  };
}
