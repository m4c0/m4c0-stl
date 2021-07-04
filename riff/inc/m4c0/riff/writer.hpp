#pragma once

#include <type_traits>

namespace m4c0::riff {
  class writer {
  public:
    // TODO: Error handling
    virtual void write(const void * buffer, unsigned len) = 0;
    virtual void seekp(unsigned pos) = 0;
    virtual unsigned tellp() = 0;

    template<class Tp>
    auto write(const Tp & tp) -> std::enable_if_t<std::is_standard_layout_v<Tp> && !std::is_pointer_v<Tp>> {
      write(&tp, sizeof(Tp));
    }
  };
}
