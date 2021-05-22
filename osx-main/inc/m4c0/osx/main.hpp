#pragma once

#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/objc/ns_event.hpp"

namespace m4c0::osx {
  class delegate {
  public:
    virtual void start(const objc::mtk_view * view) = 0;
    virtual void on_event(const objc::ns_event * e) = 0;
    virtual void stop() = 0;
  };

  int main(int argc, char ** argv, delegate * d);
}
