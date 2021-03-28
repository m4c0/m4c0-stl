#pragma once

namespace m4c0::objc {
  using imp_t = void (*)();

  struct static_inject {
    template<typename Fn>
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    static_inject(const char * sel_name, Fn fn) noexcept : static_inject(sel_name, reinterpret_cast<imp_t>(fn)) {
    }
    static_inject(const char * sel_name, imp_t imp) noexcept;
  };
}
