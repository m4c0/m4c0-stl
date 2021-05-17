#pragma once

#include "m4c0/objc/ns_event_modifier_flags.hpp"
#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_menu;

  class ns_menu_item : public ns_object {
    using ns_object::ns_object;

  public:
    ns_menu_item() : ns_object("NSMenuItem") {};

    void set_submenu(const ns_menu * menu);

    ns_event_modifier_flags key_equivalent_modifier_mask();
    void key_equivalent_modifier_mask(ns_event_modifier_flags mask);

    static ns_menu_item with_title_action_key(const char * title, const char * sel, const char * key);
    static ns_menu_item separator_item() {
      return ns_menu_item { "NSMenuItem", "separatorItem" };
    }
  };
}
