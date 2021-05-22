#pragma once

#include "m4c0/objc/ns_object.hpp"
namespace m4c0::objc {
  class ns_event : public ns_object {
  public:
    explicit ns_event(void * obj) : ns_object(obj) {
    }
  };
}
