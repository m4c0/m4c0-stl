#pragma once

#include "m4c0/native_handles.hpp"

#include <memory>
#include <span>

namespace m4c0::assets {
  class simple_asset {
  public:
    simple_asset() = default;
    virtual ~simple_asset() = default;

    simple_asset(simple_asset &&) = delete;
    simple_asset(const simple_asset &) = delete;
    simple_asset & operator=(simple_asset &&) = delete;
    simple_asset & operator=(const simple_asset &) = delete;

    [[nodiscard]] virtual const void * data() const noexcept = 0;
    [[nodiscard]] virtual unsigned size() const noexcept = 0;

    template<class Tp>
    [[nodiscard]] std::span<const Tp> span(unsigned offset = 0) const noexcept {
      auto bytes = span<std::byte>(offset);
      const void * data = bytes.data();
      return { static_cast<const Tp *>(data), bytes.size() };
    }
    template<>
    [[nodiscard]] std::span<const std::byte> span<std::byte>(unsigned offset) const noexcept {
      return std::span { static_cast<const std::byte *>(data()), size() }.subspan(offset);
    }

    static std::unique_ptr<simple_asset> load(const native_handles * nptr, const char * name, const char * ext);
  };
}
