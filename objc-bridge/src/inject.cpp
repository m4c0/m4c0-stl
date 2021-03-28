#include "m4c0/objc/inject.hpp"
#include "m4c0/objc/middleware.hpp"

using namespace m4c0::objc;

static_inject::static_inject(const char * sel_name, imp_t imp) noexcept {
  middleware::instance().add_imp(sel_name, imp);
}
