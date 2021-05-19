#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_menu.hpp"
#include "m4c0/objc/ns_window.hpp"

using namespace m4c0::objc;

ns_application ns_application::shared_application() {
  return ns_application("NSApplication", "sharedApplication");
}

ns_window ns_application::main_window() {
  void * obj = objc_msg_send<void *>(self(), "mainWindow");
  return ns_window { obj };
}

void ns_application::set_delegate(const ns_object * d) {
  objc_msg_send<void>(self(), "setDelegate:", d->self());
}
void ns_application::set_main_menu(const ns_menu * m) {
  objc_msg_send<void>(self(), "setMainMenu:", m->self());
}

void ns_application::activate_ignoring_other_apps(bool b) {
  objc_msg_send<void>(self(), "activateIgnoringOtherApps:", b ? YES : NO);
}
void ns_application::run() {
  objc_msg_send<void>(self(), "run");
}
