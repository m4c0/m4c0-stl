#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/middleware.hpp"

static auto dummy() {
  return 3;
}

namespace m4c0::objc {
  class inject {
  public:
    template<typename Fn>
    inject(const char * sel_name, Fn fn) noexcept {
      middleware::instance().add_forward(sel_name, fn);
    }
  };
}

static const m4c0::objc::inject i { "length", &dummy };

int main() {
  m4c0::objc::autorelease_pool pool;

  void * obj = m4c0::objc::middleware::instance().create_for("NSString");
  return dummy() - m4c0::objc::objc_msg_send<int>(obj, "length");
}
