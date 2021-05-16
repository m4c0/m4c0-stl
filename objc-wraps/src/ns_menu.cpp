#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_menu.hpp"
#include "m4c0/objc/ns_menu_item.hpp"

using namespace m4c0::objc;

void ns_menu::add_item(const ns_menu_item * item) {
  objc_msg_send<void>(self(), "addItem:", item->self());
}
