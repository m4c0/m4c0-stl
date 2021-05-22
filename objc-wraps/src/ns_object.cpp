#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_object.hpp"

using namespace m4c0::objc;

ns_object::ns_object(void * obj) : m_object(obj) {
  objc_msg_send<void>(m_object, "retain");
}
ns_object::ns_object(const char * cls_name) : ns_object(cls_name, "alloc", false) {
  m_object = objc_msg_send<void *>(m_object, "init");
}
ns_object::ns_object(const char * cls_name, const char * method, bool retain)
  : m_object(objc_msg_send<objc_object *>(objc_getClass(cls_name), method)) {
  if (retain) objc_msg_send<void>(m_object, "retain");
}
ns_object::~ns_object() {
  objc_msg_send<void>(m_object, "release");
}

ns_object::ns_object(const ns_object & o) : m_object(o.m_object) {
  objc_msg_send<void>(m_object, "retain");
}
ns_object & ns_object::operator=(const ns_object & o) {
  if (&o == this) return *this;

  objc_msg_send<void>(m_object, "release");
  m_object = o.m_object;
  objc_msg_send<void>(m_object, "retain");
  return *this;
}

template<>
cg_rect ns_object::get(const char * getter) const {
  return objc_msg_send<cg_rect>(self(), getter);
}
template<>
void ns_object::set(const char * setter, const ns_object & o) const {
  objc_msg_send<void>(self(), setter, o.self());
}
template<>
void ns_object::set(const char * setter, const cg_rect & o) const {
  objc_msg_send<void>(self(), setter, o);
}

void ns_object::send(const char * msg) const {
  objc_msg_send<void>(self(), msg);
}
