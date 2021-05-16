#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_menu.hpp"
#include "m4c0/objc/ns_menu_item.hpp"

#include <CoreFoundation/CoreFoundation.h>

using namespace m4c0::objc;

ns_menu_item ns_menu_item::with_title_action_key(const char * title, const char * sel, const char * key) {
  ns_object res { "NSMenuItem", "alloc" };

  CFStringRef t = CFStringCreateWithCString(nullptr, title, kCFStringEncodingUTF8);
  SEL s = sel_getUid(sel);
  CFStringRef k = CFStringCreateWithCString(nullptr, key, kCFStringEncodingUTF8);

  void * obj = objc_msg_send<void *>(res.self(), "initWithTitle:action:keyEquivalent:", t, s, k);
  return ns_menu_item { "NSMenuItem", obj };
}

void ns_menu_item::set_submenu(const ns_menu * menu) {
  objc_msg_send<void>(self(), "setSubmenu:", menu->self());
}
