#pragma once

#include "m4c0/vulkan/loader.hpp"

#include <utility>
#include <vector>

namespace m4c0::vulkan::details {
  void check(VkResult);

  template<typename Fn, typename... Args>
  void safe_call(Fn fn, Args &&... args) {
    check(fn(std::forward<Args>(args)...));
  }
  template<typename Fn, typename... Args>
  void safe_call_d(Fn fn, Args &&... args) {
    safe_call(fn, loader::get_device(), std::forward<Args>(args)...);
  }

  template<typename Out, typename... Args>
  Out safe_create(Args &&... args) {
    Out out {};
    safe_call(std::forward<Args>(args)..., nullptr, &out);
    return out;
  }
  template<typename Out, typename Fn, typename... Args>
  Out safe_create_d(Fn fn, Args &&... args) {
    return safe_create<Out>(fn, loader::get_device(), std::forward<Args>(args)...);
  }

  template<class Out, class Fn, class... Args>
  auto safe_enumerate(Fn fn, Args &&... args) {
    unsigned count {};
    safe_call(fn, std::forward<Args>(args)..., &count, nullptr);

    std::vector<Out> res { count };
    safe_call(fn, std::forward<Args>(args)..., &count, res.data());
    return res;
  }

  template<class Out, class Fn, class... Args>
  auto unsafe_enumerate(Fn fn, Args &&... args) {
    unsigned count {};
    fn(std::forward<Args>(args)..., &count, nullptr);

    std::vector<Out> res { count };
    fn(std::forward<Args>(args)..., &count, res.data());
    return res;
  }

  template<class Fn, class Arg>
  void safe_destroy_d(Fn fn, Arg * arg) {
    // The only real benefit of this wrapper is to provide a common place for a debug breakpoint
    fn(loader::get_device(), arg->pointer(), nullptr);
  }
}
