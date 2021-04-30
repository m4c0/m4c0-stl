#pragma once

namespace m4c0::objc {
  using imp_t = void (*)();

  struct static_inject {
    template<typename Ret, typename... Args>
    static_inject(const char * sel_name, Ret (*fn)(void * id, void * self, Args...)) noexcept
      : static_inject(sel_name, reinterpret_cast<imp_t>(fn)) { // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }
    template<typename Ret>
    static_inject(const char * sel_name, Ret (*fn)()) noexcept
      : static_inject(sel_name, reinterpret_cast<imp_t>(fn)) { // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    }
    static_inject(const char * sel_name, imp_t imp) noexcept;
  };
}
