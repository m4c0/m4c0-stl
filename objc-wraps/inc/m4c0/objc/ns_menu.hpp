#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_menu_item;

  class ns_menu : public ns_object {
    using ns_object::ns_object;

  public:
    ns_menu() : ns_object("NSMenu") {
    }

    void add_item(const ns_menu_item * item);
    void add_item(const ns_menu_item & item) {
      add_item(&item);
    }
  };
}
