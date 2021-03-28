#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/middleware.hpp"

#include <objc/message.h>
#include <objc/runtime.h>
#include <string>
#include <unordered_map>

using namespace m4c0::objc;

class middleware::data {
  std::unordered_map<const char *, Class> m_class_cache {};
  std::unordered_map<const char *, IMP> m_imps {};

public:
  data() = default;
  ~data() {
    for (auto & kv : m_class_cache) {
      objc_disposeClassPair(kv.second);
    }
  }
  data(data &&) = delete;
  data(const data &) = delete;
  data & operator=(data &&) = delete;
  data & operator=(const data &) = delete;

  Class create_class(const char * base_class_name) {
    using namespace std::literals;
    std::string name = "M4C0_$$_"s + base_class_name;
    Class super = objc_getClass(base_class_name);
    Class cls = objc_allocateClassPair(super, name.c_str(), 0);
    for (auto & kv : m_imps) {
      Method m = class_getInstanceMethod(super, sel_getUid(kv.first));
      if (m == nullptr) continue;

      const char * sign = method_getTypeEncoding(m);
      SEL sel = sel_getUid(kv.first);
      class_addMethod(cls, sel, kv.second, sign);
    }
    objc_registerClassPair(cls);
    return cls;
  }
  Class get_class(const char * base_class_name) {
    auto & cls = m_class_cache[base_class_name];
    if (cls == nullptr) cls = create_class(base_class_name);
    return cls;
  }

  void add_imp(const char * sel_name, void (*imp)()) {
    m_imps[sel_name] = imp;
  }
};

middleware::~middleware() = default;
void * middleware::create_for(const char * base_class_name) {
  Class cls = m_data->get_class(base_class_name);
  void * result = objc_msg_send<void *>(cls, "new");
  return objc_msg_send<void *>(result, "autorelease");
}
void middleware::add_imp(const char * sel_name, void (*imp)()) {
  m_data->add_imp(sel_name, imp);
}
