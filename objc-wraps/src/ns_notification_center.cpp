#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_notification_center.hpp"

#include <objc/runtime.h>

using namespace m4c0::objc;

ns_notification_center ns_notification_center::default_center() {
  return ns_notification_center { "NSNotificationCenter", "defaultCenter" };
}

void ns_notification_center::add_observer(
    const ns_object * observer,
    const char * sel,
    const char * name,
    const ns_object * object) {
  void * os = observer->self();
  void * s = sel_getUid(sel);
  void * ob = object->self();
  objc_msg_send<void>(self(), "addObserver:selector:name:object:", os, s, name, ob);
}
void ns_notification_center::remove_observer(const ns_object * observer, const char * name, const ns_object * object) {
  void * os = observer->self();
  void * ob = object->self();
  objc_msg_send<void>(self(), "removeObserver:selector:name:object:", os, name, ob);
}
