#pragma once

#include <objc/message.h>
#include <objc/runtime.h>
#include <utility>

// ARM64, for reasons
#if !defined(__i386__) && !defined(__x86_64__)
#define objc_msgSend_stret objc_msgSend
#define objc_msgSend_fpret objc_msgSend
#endif

namespace m4c0::objc {
  namespace details {
    // This only works because we have three options (as of 2021) in Apple's world of things:
    // x86 (which may be history by now), x86_64 (where it "just works") and arm64 (works
    // because "stret" isn't a thing on ARM)
    template<class Tp>
    static constexpr const auto fits_in_intel_return_v = (sizeof(Tp) <= 2 * sizeof(void *));
    template<>
    static constexpr const auto fits_in_intel_return_v<void> = true;

    template<typename Ret, typename... Args>
    static Ret call(void (*fn)(), void * obj, const char * sel_name, Args... args) {
      SEL sel = sel_getUid(sel_name);
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      return reinterpret_cast<Ret (*)(void *, SEL, Args...)>(fn)(obj, sel, args...);
    }
  }

  template<typename Ret, typename... Args>
  static auto objc_msg_send(void * obj, const char * sel_name, Args... args)
      -> std::enable_if_t<!std::is_floating_point_v<Ret> && !std::is_class_v<Ret>, Ret> {
    return details::call<Ret>(&objc_msgSend, obj, sel_name, args...);
  }
  template<typename Ret, typename... Args>
  static auto objc_msg_send(void * obj, const char * sel_name, Args... args)
      -> std::enable_if_t<std::is_floating_point_v<Ret>, Ret> {
    return details::call<Ret>(&objc_msgSend_fpret, obj, sel_name, args...);
  }
  // Welcome to the true dynamic nature of objc_msgSend: the ObjC compiler adds a lot of sugar to the syntax of
  // messages. One of them regards how to deal with "structs" in return signatures while being C-compatible. The answer
  // is: I'm glad this ABI is compatible with C++ for the same requirement. In a nutshell, anything smaller than two
  // Intel CPU registers is returned inside registers (RAX+DAX and XMM0+XMM1) - anything bigger becomes a pointer to the
  // caller's stack (i.e. require the stret call).
  template<typename Ret, typename... Args>
  static auto objc_msg_send(void * obj, const char * sel_name, Args... args)
      -> std::enable_if_t<std::is_class_v<Ret> && details::fits_in_intel_return_v<Ret>, Ret> {
    return details::call<Ret>(&objc_msgSend, obj, sel_name, args...);
  }
  template<typename Ret, typename... Args>
  static auto objc_msg_send(void * obj, const char * sel_name, Args... args)
      -> std::enable_if_t<std::is_class_v<Ret> && !details::fits_in_intel_return_v<Ret>, Ret> {
    return details::call<Ret>(&objc_msgSend_stret, obj, sel_name, args...);
  }
  template<typename Ret, typename... Args>
  static Ret objc_msg_send_super(const char * super_class, void * obj, const char * sel_name, Args... args) {
    id self = static_cast<id>(obj);
    SEL sel = sel_getUid(sel_name);

    objc_super s {};
    s.super_class = objc_getClass(super_class); // We can't infer if calling from super itself
    s.receiver = self;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<Ret (*)(objc_super *, SEL, Args...)>(objc_msgSendSuper)(&s, sel, args...);
  }

  template<class Tp>
  static Tp object_get_ivar(void * self, const char * ivar_name) {
    id self_id = static_cast<id>(self);
    Ivar ivar = object_getInstanceVariable(self_id, ivar_name, nullptr);
    if (!ivar) return Tp {};

    return *reinterpret_cast<Tp *>(static_cast<std::byte *>(self) + ivar_getOffset(ivar)); // NOLINT
  }
  template<class Tp>
  static void object_set_ivar(void * self, const char * ivar_name, Tp ptr) {
    id self_id = static_cast<id>(self);
    Ivar ivar = object_getInstanceVariable(self_id, ivar_name, nullptr);
    if (!ivar) return;

    *reinterpret_cast<Tp *>(static_cast<std::byte *>(self) + ivar_getOffset(ivar)) = ptr; // NOLINT
  }

  template<typename Ret, typename... Args>
  static IMP to_imp(Ret (*fn)(Args...)) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return *reinterpret_cast<IMP *>(&fn);
  }
}
