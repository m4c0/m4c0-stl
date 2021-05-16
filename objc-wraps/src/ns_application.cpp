#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_application.hpp"

using namespace m4c0::objc;

ns_application ns_application::shared_application() {
  return ns_application("NSApplication", "sharedApplication");
}

void ns_application::set_delegate(const ns_object * d) {
  objc_msg_send<void>(self(), "setDelegate:", d->self());
}

void ns_application::run() {
  objc_msg_send<void>(self(), "run");
}
