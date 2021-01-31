#pragma once

#include "m4c0/di.hpp"

namespace m4c0::di {
  class scope {
    config m_cfg {};
    injector m_injector {};
    scope * m_parent {};
    bool m_injected = false;

    [[nodiscard]] injector * get_injector() {
      if (!m_injected) {
        auto * parent_injector = m_parent != nullptr ? m_parent->get_injector() : nullptr;
        m_injector = m_cfg.build_injector(parent_injector);
        m_injected = true;
      }
      return &m_injector;
    }

  public:
    constexpr scope() = default;
    explicit scope(scope * parent) : m_parent(parent) {
    }

    template<class Tp, class... Deps>
    void bind() {
      m_cfg.bind<Tp, Deps...>();
    }

    template<class Tp>
    Tp * get() {
      return get_injector()->get<Tp>();
    }

    void reset() {
      if (m_injected) m_injector.reset();
      m_injected = false;
    }
  };
}
