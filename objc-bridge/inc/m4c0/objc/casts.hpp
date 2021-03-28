#pragma once

#include <objc/message.h>
#include <objc/runtime.h>

namespace m4c0::objc {
  template<typename Ret>
  static Ret objc_msg_send(void * obj, const char * sel_name) {
    SEL sel = sel_getUid(sel_name);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<Ret (*)(void *, SEL)>(objc_msgSend)(obj, sel);
  }
  template<typename Ret>
  static Ret objc_msg_send_super(id self, SEL sel) {
    objc_super s {};
    s.super_class = class_getSuperclass(object_getClass(self));
    s.receiver = self;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<Ret (*)(objc_super *, void *, SEL)>(objc_msgSendSuper)(&s, self, sel);
  }

  template<typename Ret, typename... Args>
  static IMP to_imp(Ret (*fn)(Args...)) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return *reinterpret_cast<IMP *>(&fn);
  }
}
