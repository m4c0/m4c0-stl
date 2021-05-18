#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_application_delegate.hpp"
#include "m4c0/objc/ns_window.hpp"

static constexpr const auto magic_number = 0xcafebabe;

class delegate : public m4c0::objc::ns_application_delegate {
public:
  void application_will_terminate(void * ptr) override {
    *static_cast<unsigned *>(ptr) = magic_number;
  }
};

int main() {
  m4c0::objc::autorelease_pool pool;

  delegate app_del;

  unsigned magic = 0;
  m4c0::objc::objc_msg_send<void>(app_del.self(), "applicationWillTerminate:", &magic);

  return magic == magic_number ? 0 : 1;
}
