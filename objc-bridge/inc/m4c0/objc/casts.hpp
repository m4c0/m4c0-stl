#pragma once

#include <objc/message.h>
#include <objc/runtime.h>
#include <utility>

namespace m4c0::objc {
  template<typename Ret, typename... Args>
  static Ret objc_msg_send(void * obj, const char * sel_name, Args &&... args) {
    SEL sel = sel_getUid(sel_name);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<Ret (*)(void *, SEL, Args...)>(objc_msgSend)(obj, sel, std::forward<Args>(args)...);
  }
  template<typename Ret, typename... Args>
  static Ret objc_msg_send_super(id self, SEL sel, Args &&... args) {
    objc_super s {};
    s.super_class = class_getSuperclass(object_getClass(self));
    s.receiver = self;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<Ret (*)(objc_super *, void *, SEL, Args...)>(
        objc_msgSendSuper)(&s, self, sel, std::forward<Args>(args)...);
  }

  template<typename Ret, typename... Args>
  static IMP to_imp(Ret (*fn)(Args...)) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return *reinterpret_cast<IMP *>(&fn);
  }
}
