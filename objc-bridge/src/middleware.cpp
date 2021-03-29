#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/middleware.hpp"

#include <objc/message.h>
#include <objc/runtime.h>
#include <string>
#include <unordered_map>

using namespace m4c0::objc;

class middleware::data {
  std::unordered_map<const char *, Class> m_class_cache {};
  std::unordered_map<const char *, Class> m_proto_cache {};
  std::unordered_map<const char *, IMP> m_imps {};

  Class create_protocol(const char * proto_name) {
    using namespace std::literals;
    std::string name = "M4C0_!!_"s + proto_name;
    Class super = objc_getClass("NSObject");
    Class cls = objc_allocateClassPair(super, name.c_str(), 0);
    Protocol * proto = objc_getProtocol(proto_name);
    // TODO: check for nullptr
    class_addProtocol(cls, proto);
    for (auto & kv : m_imps) {
      auto m = protocol_getMethodDescription(proto, sel_getUid(kv.first), YES, YES);
      if (m.name == nullptr) {
        m = protocol_getMethodDescription(proto, sel_getUid(kv.first), NO, YES);
      }
      if (m.name == nullptr) continue;

      class_addMethod(cls, m.name, kv.second, m.types);
    }
    objc_registerClassPair(cls);
    return cls;
  }

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

public:
  data() = default;
  ~data() {
    for (auto & kv : m_class_cache) {
      objc_disposeClassPair(kv.second);
    }
    for (auto & kv : m_proto_cache) {
      objc_disposeClassPair(kv.second);
    }
  }
  data(data &&) = delete;
  data(const data &) = delete;
  data & operator=(data &&) = delete;
  data & operator=(const data &) = delete;

  Class get_class(const char * base_class_name) {
    auto & cls = m_class_cache[base_class_name];
    if (cls == nullptr) cls = create_class(base_class_name);
    return cls;
  }
  Class get_protocol(const char * proto_name) {
    auto & cls = m_proto_cache[proto_name];
    if (cls == nullptr) cls = create_protocol(proto_name);
    return cls;
  }

  void add_imp(const char * sel_name, void (*imp)()) {
    m_imps[sel_name] = imp;
  }
};

middleware::middleware() {
  m_data.make_new();
}
middleware::~middleware() = default;

void * middleware::create_for_class(const char * base_class_name) {
  Class cls = m_data->get_class(base_class_name);
  void * result = objc_msg_send<void *>(cls, "new");
  return objc_msg_send<void *>(result, "autorelease");
}
void * middleware::create_for_protocol(const char * proto_name) {
  Class cls = m_data->get_protocol(proto_name);
  void * result = objc_msg_send<void *>(cls, "new");
  return objc_msg_send<void *>(result, "autorelease");
}

void middleware::add_imp(const char * sel_name, void (*imp)()) {
  m_data->add_imp(sel_name, imp);
}
