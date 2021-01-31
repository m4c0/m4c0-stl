#pragma once

#include "m4c0/di/type_id.hpp"
#include "m4c0/function.hpp"
#include "m4c0/pimpl.hpp"

#include <array>
#include <memory>
#include <span>

namespace m4c0::di {
  template<class Tp, class Deleter, class... Deps>
  using factory_t = std::unique_ptr<Tp, Deleter> (*)(Deps *...);

  class injector {
    friend class config;
    class data;

    pimpl<data> m_data {};
    injector * m_parent {};

    explicit injector(unsigned size, injector * parent);

    [[nodiscard]] void * raw_get(int id) const;
    [[nodiscard]] void * get_ptr(unsigned loc);

    void put(int id, void * ptr, void (*deleter)(void *));

    template<class Tp, class... Deps>
    void put(unsigned loc) {
      Tp * i = ::new (get_ptr(loc)) Tp(get<Deps>()...); // NOLINT
      auto deleter = [](void * ptr) {
        std::destroy_at(static_cast<Tp *>(ptr));
      };
      put(type_id::of<Tp>(), i, deleter);
    }

  public:
    injector() = default;

    void reset() noexcept;

    template<class Tp>
    [[nodiscard]] Tp * get() const {
      return static_cast<Tp *>(raw_get(type_id::of<Tp>()));
    }

    template<class Tp, class Deleter, class... Deps>
    std::unique_ptr<Tp, Deleter> inject(factory_t<Tp, Deleter, Deps...> factory) const {
      return factory(get<Deps>()...);
    }
  };

  class config {
    using init_fn_t = m4c0::function<void(injector &, unsigned)>;

    class graph;
    class node_info;
    pimpl<graph> m_graph {};
    unsigned m_size {};

    void add_node(init_fn_t && fn, int tp, std::span<int> deps, unsigned size, unsigned align);

  public:
    config();

    template<class Tp, class... Deps>
    void bind() {
      std::array<int, sizeof...(Deps)> deps { type_id::of<Deps>()... };
      auto fn = [](injector & i, unsigned loc) {
        i.put<Tp, Deps...>(loc);
      };
      add_node(std::move(fn), type_id::of<Tp>(), deps, sizeof(Tp), alignof(Tp));
    }

    [[nodiscard]] injector build_injector(injector * parent = nullptr);
  };
}
