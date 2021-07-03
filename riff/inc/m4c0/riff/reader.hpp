#pragma once

#include <optional>

namespace m4c0::riff {
  class reader {
    friend class subreader;

  protected:
    [[nodiscard]] virtual bool read(void * buffer, unsigned len) = 0;

  public:
    [[nodiscard]] virtual bool seekg(unsigned pos) = 0;
    [[nodiscard]] virtual unsigned tellg() = 0;

    template<class Tp>
    [[nodiscard]] std::optional<Tp> read() {
      static_assert(std::is_trivial_v<Tp>);
      Tp res {};
      if (read(&res, sizeof(res))) {
        return { res };
      }
      return {};
    }
  };
}
