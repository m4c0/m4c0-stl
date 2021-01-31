#pragma once

#include <type_traits>

namespace m4c0::di {
  class type_id {
    static int new_id();

    template<class Key>
    static int raw_type_id() {
      static int id = new_id();
      return id;
    }

  public:
    template<class Key>
    static int of() {
      return raw_type_id<std::decay_t<Key>>();
    }
  };
}
