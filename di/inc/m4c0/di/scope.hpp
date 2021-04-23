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

  /// \brief Convenience for statically defining a class scope.
  ///
  /// It requires a scope creator function like this:
  ///
  ///   m4c0::di::scope * my_scope() {
  ///     static m4c0::di::scope instance {};
  ///     return &instance;
  ///   }
  ///
  /// Then, instances of Tp can be defined like this in a module:
  ///
  ///   static m4c0::di::static_bind<my_scope, my_class, parm_1, parm_2> b;
  ///
  /// This will add "my_class" to "my_scope" and an instance will be added by injecting a pointer to "parm_1" and
  /// "parm_2", assuming that class has a suitable constructor and both parms are bound to the same scope.
  template<m4c0::di::scope * (*Scope)(), typename Tp, typename... Deps>
  struct static_bind {
    static_bind() noexcept {
      Scope()->bind<Tp, Deps...>();
    }
    ~static_bind() = default;

    static_bind(static_bind &&) = delete;
    static_bind(const static_bind &) = delete;
    static_bind & operator=(static_bind &&) = delete;
    static_bind & operator=(const static_bind &) = delete;
  };

  /// \brief RAII guard of a scope
  ///
  /// This helps defining the lifecycle of a scope. Example:
  ///
  ///   m4c0::di::scope * my_scope();
  ///
  ///   struct my_obj {
  ///     void do_something();
  ///   };
  ///   static m4c0::di::static_bind<my_scope, my_object> b;
  ///
  ///   void use_scope() {
  ///     m4c0::di::scope_guard<my_scope> guard;
  ///     guard->get<my_obj>()->do_something();
  ///   }
  ///
  /// The scope gets reset when the guard is destructed.
  template<m4c0::di::scope * (*Scope)()>
  struct scope_guard {
    scope_guard() noexcept = default;
    ~scope_guard() {
      Scope()->reset();
    }

    scope_guard(scope_guard &&) = delete;
    scope_guard(const scope_guard &) = delete;
    scope_guard & operator=(scope_guard &&) = delete;
    scope_guard & operator=(const scope_guard &) = delete;

    template<class Tp>
    auto get() const {
      return Scope()->get<Tp>();
    }
  };
}
