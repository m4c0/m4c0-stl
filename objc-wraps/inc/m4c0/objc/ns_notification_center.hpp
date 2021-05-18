#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_notification_center : public ns_object {
    using ns_object::ns_object;

  public:
    void add_observer(const ns_object * observer, const char * sel, const char * name, const ns_object * object);
    void remove_observer(const ns_object * observer, const char * name, const ns_object * object);

    [[nodiscard]] static ns_notification_center default_center();
  };
}
