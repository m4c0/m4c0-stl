#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/inject.hpp"
#include "m4c0/objc/middleware.hpp"

static auto dummy(void * /*self*/) {
  return 3;
}

static const m4c0::objc::static_inject i { "length", &dummy };

int main() {
  m4c0::objc::autorelease_pool pool;

  void * obj = m4c0::objc::middleware::instance().create_for("NSString");
  return dummy(nullptr) - m4c0::objc::objc_msg_send<int>(obj, "length");
}
