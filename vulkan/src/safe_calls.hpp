#pragma once

#include "m4c0/vulkan/loader.hpp"

#include <utility>

namespace m4c0::vulkan::details {
  void check(VkResult);

  template<typename Fn, typename... Args>
  void safe_call(Fn fn, Args &&... args) {
    check(fn(std::forward<Args>(args)...));
  }

  template<typename Out, typename... Args>
  Out safe_create(Args &&... args) {
    Out out {};
    safe_call(std::forward<Args>(args)..., nullptr, &out);
    return out;
  }

  template<class Out, class Fn, class... Args>
  auto safe_enumerate(Fn fn, Args &&... args) {
    unsigned count {};
    safe_call(fn, std::forward<Args>(args)..., &count, nullptr);

    std::vector<Out> res { count };
    safe_call(fn, std::forward<Args>(args)..., &count, res.data());
    return res;
  }
}
