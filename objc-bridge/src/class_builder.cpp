#include "m4c0/objc/class_builder.hpp"

#include <string>

using namespace m4c0::objc;

static std::string unique_class_name(const char * parent) {
  static int counter = 0;
  using namespace std::string_literals;
  return "M4C0_$$_"s + parent + "_" + std::to_string(++counter);
}

class_builder::class_builder(const char * parent)
  : m_class(objc_allocateClassPair(objc_getClass(parent), unique_class_name(parent).c_str(), 0)) {
}

class_builder & class_builder::add_ivar(const char * name, unsigned int size, unsigned int align, const char * sign) {
  class_addIvar(static_cast<Class>(m_class), name, size, log2(align), sign);
  return *this;
}

class_builder & class_builder::add_method(const char * sel, imp_t imp, const char * sign) {
  class_addMethod(static_cast<Class>(m_class), sel_getUid(sel), imp, sign);
  return *this;
}

const char * class_builder::build() {
  auto * cls = static_cast<Class>(m_class);
  objc_registerClassPair(cls);
  return class_getName(cls);
}
