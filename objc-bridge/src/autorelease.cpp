#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"

using namespace m4c0::objc;

static auto new_pool() {
  auto * ar_cls = objc_getClass("NSAutoreleasePool");
  return objc_msg_send<id>(ar_cls, "new");
}

autorelease_pool::autorelease_pool() : m_ar(new_pool()) {
}
autorelease_pool::~autorelease_pool() {
  objc_msg_send<void>(m_ar, "drain");
}
