#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_object.hpp"

using namespace m4c0::objc;

ns_object::ns_object(const char * cls_name) : ns_object(cls_name, "alloc") {
  objc_msg_send<void>(m_object, "init");
}
ns_object::ns_object(const char * cls_name, const char * method)
  : m_class(objc_getClass(cls_name))
  , m_object(objc_msg_send<objc_object *>(m_class, method)) {
}
ns_object::~ns_object() {
  objc_msg_send<void>(m_object, "release");
}

ns_object::ns_object(const ns_object & o) : m_class(o.m_class), m_object(o.m_object) {
  objc_msg_send<void>(m_object, "retain");
}
ns_object & ns_object::operator=(const ns_object & o) {
  if (&o == this) return *this;

  m_class = o.m_class;
  m_object = o.m_object;
  objc_msg_send<void>(m_object, "retain");
  return *this;
}
