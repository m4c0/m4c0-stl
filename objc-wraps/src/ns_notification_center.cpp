#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_notification_center.hpp"
#include "m4c0/objc/ns_string.hpp"

#include <objc/runtime.h>

using namespace m4c0::objc;

ns_notification_center ns_notification_center::default_center() {
  return ns_notification_center { "NSNotificationCenter", "defaultCenter", true };
}

void ns_notification_center::add_observer(
    const ns_object * observer,
    const char * sel,
    const char * name,
    const ns_object * object) {
  ns_string nm = ns_string::with_cstring_utf8(name);
  void * os = observer->self();
  void * s = sel_getUid(sel);
  void * ob = object->self();
  objc_msg_send<void>(self(), "addObserver:selector:name:object:", os, s, nm.self(), ob);
}
void ns_notification_center::remove_observer(const ns_object * observer, const char * name, const ns_object * object) {
  ns_string nm = ns_string::with_cstring_utf8(name);
  void * os = observer->self();
  void * ob = object->self();
  objc_msg_send<void>(self(), "removeObserver:selector:name:object:", os, nm.self(), ob);
}
