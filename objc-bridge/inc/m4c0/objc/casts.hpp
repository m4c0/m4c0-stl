#pragma once

#include <objc/message.h>
#include <objc/runtime.h>
#include <utility>

// ARM64, for reasons
#ifndef objc_msgSend_stret
#define objc_msgSend_stret objc_msgSend
#endif
#ifndef objc_msgSend_fpret
#define objc_msgSend_fpret objc_msgSend
#endif

namespace m4c0::objc {
  namespace details {
    template<typename Ret, typename... Args>
    static Ret call(void (*fn)(), void * obj, const char * sel_name, Args &&... args) {
      SEL sel = sel_getUid(sel_name);
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      return reinterpret_cast<Ret (*)(void *, SEL, Args...)>(fn)(obj, sel, std::forward<Args>(args)...);
    }
  }

  template<typename Ret, typename... Args>
  static auto objc_msg_send(void * obj, const char * sel_name, Args &&... args)
      -> std::enable_if_t<!std::is_floating_point_v<Ret> && !std::is_class_v<Ret>, Ret> {
    return details::call<Ret>(&objc_msgSend, obj, sel_name, std::forward<Args>(args)...);
  }
  template<typename Ret, typename... Args>
  static auto objc_msg_send(void * obj, const char * sel_name, Args &&... args)
      -> std::enable_if_t<std::is_floating_point_v<Ret>, Ret> {
    return details::call<Ret>(&objc_msgSend_fpret, obj, sel_name, std::forward<Args>(args)...);
  }
  template<typename Ret, typename... Args>
  static auto objc_msg_send(void * obj, const char * sel_name, Args &&... args)
      -> std::enable_if_t<std::is_class_v<Ret>, Ret> {
    return details::call<Ret>(&objc_msgSend_stret, obj, sel_name, std::forward<Args>(args)...);
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