#pragma once

#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_menu.hpp"
#include "m4c0/objc/ns_menu_item.hpp"

#include <string>

static auto add_item(m4c0::objc::ns_menu * m, const char * title, const char * sel, const char * key) {
  auto res = m4c0::objc::ns_menu_item::with_title_action_key(title, sel, key);
  m->add_item(res);
  return res;
}
static auto add_item(m4c0::objc::ns_menu * m, const std::string & title, const char * sel, const char * key) {
  return add_item(m, title.c_str(), sel, key);
}

static void setup_apple_menu(m4c0::objc::ns_application * app, const char * title) {
  using namespace m4c0::objc;

  ns_menu bar;
  ns_menu_item app_item;
  ns_menu app_menu;

  using namespace std::string_literals;
  add_item(&app_menu, "Hide "s + title, "hide:", "h");
  auto ho = add_item(&app_menu, "Hide Others", "hideOtherApplications:", "h");
  add_item(&app_menu, "Show All", "unhideAllApplications:", "");
  app_menu.add_item(ns_menu_item::separator_item());
  add_item(&app_menu, "Quit "s + title, "terminate:", "q");

  ho.key_equivalent_modifier_mask(ho.key_equivalent_modifier_mask() | ns_event_modifier_flags::option);

  app_item.set_submenu(&app_menu);
  bar.add_item(app_item);
  app->set_main_menu(&bar);
}
