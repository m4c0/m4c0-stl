#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/middleware.hpp"

#include <objc/message.h>
#include <objc/runtime.h>
#include <string>
#include <unordered_map>

using namespace m4c0::objc;

class middleware::data {
  static char prefix;

  std::unordered_map<const char *, Class> m_class_cache {};
  std::unordered_map<const char *, Class> m_proto_cache {};
  std::unordered_map<const char *, IMP> m_imps {};
  std::string m_prefix;

  Class create_protocol(const char * proto_name) {
    std::string name = m_prefix + "_!!_" + proto_name;
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
    std::string name = m_prefix + "_$$_" + base_class_name;
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
  data() : m_prefix(std::string("M4C0_") + prefix++) {
  }
  ~data() = default;
  // ObjC runtime isn't pretty in a real-world scenario. iOS have issues de-registering classes and some child classes
  // are dynamically created in runtime by Apple, which creates a lot of noise when we cleanup.
  //
  // This code was left here as a reminder, if some kind soul wants to fix this.
  //~data() {
  //  for (auto & kv : m_class_cache) {
  //    objc_disposeClassPair(kv.second);
  //  }
  //  for (auto & kv : m_proto_cache) {
  //    objc_disposeClassPair(kv.second);
  //  }
  //}
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

char middleware::data::prefix = '0';

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
