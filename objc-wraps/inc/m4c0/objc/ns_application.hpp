#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_menu;
  class ns_window;

  class ns_application : public ns_object {
  protected:
    using ns_object::ns_object;

  public:
    static ns_application shared_application();

    [[nodiscard]] ns_window main_window();

    void set_delegate(const ns_object * d);
    void set_main_menu(const ns_menu * m);

    void activate_ignoring_other_apps(bool b);
    void run();
  };
}
