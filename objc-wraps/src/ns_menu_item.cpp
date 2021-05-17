#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_menu.hpp"
#include "m4c0/objc/ns_menu_item.hpp"
#include "m4c0/objc/ns_string.hpp"

#include <CoreFoundation/CoreFoundation.h>

using namespace m4c0::objc;

ns_menu_item ns_menu_item::with_title_action_key(const char * title, const char * sel, const char * key) {
  ns_object res { "NSMenuItem", "alloc" };

  auto t = ns_string::with_cstring_utf8(title);
  SEL s = sel_getUid(sel);
  auto k = ns_string::with_cstring_utf8(key);

  void * obj = objc_msg_send<void *>(res.self(), "initWithTitle:action:keyEquivalent:", t.self(), s, k.self());
  return ns_menu_item { "NSMenuItem", obj };
}

void ns_menu_item::set_submenu(const ns_menu * menu) {
  objc_msg_send<void>(self(), "setSubmenu:", menu->self());
}

ns_event_modifier_flags ns_menu_item::key_equivalent_modifier_mask() {
  return objc_msg_send<ns_event_modifier_flags>(self(), "keyEquivalentModifierMask");
}
void ns_menu_item::key_equivalent_modifier_mask(ns_event_modifier_flags mask) {
  objc_msg_send<void>(self(), "setKeyEquivalentModifierMask:", mask);
}
