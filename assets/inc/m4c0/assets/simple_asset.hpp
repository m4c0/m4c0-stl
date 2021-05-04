#pragma once

#include <memory>
#include <span>

namespace m4c0::assets {
  class native_provider;

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
    [[nodiscard]] std::span<const Tp> typed_data() const noexcept {
      return { static_cast<const Tp *>(data()), size() };
    }

    static std::unique_ptr<simple_asset> load(const native_provider * nptr, const char * name, const char * ext);
  };
}
