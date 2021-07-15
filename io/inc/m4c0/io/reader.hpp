#pragma once

#include <optional>

namespace m4c0::io {
  class reader {
    friend class subreader;

  public:
    [[nodiscard]] virtual bool eof() = 0;
    [[nodiscard]] virtual bool seekg(unsigned pos) = 0;
    [[nodiscard]] virtual unsigned tellg() = 0;

    [[nodiscard]] virtual bool read(void * buffer, unsigned len) = 0;
    [[nodiscard]] virtual std::optional<uint8_t> read_u8() = 0;
    [[nodiscard]] virtual std::optional<uint32_t> read_u32() = 0;
  };
}
