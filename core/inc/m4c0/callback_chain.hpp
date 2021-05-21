#pragma once

#include "m4c0/function.hpp"

#include <numeric>
#include <optional>
#include <vector>

namespace m4c0 {
  template<class Fn>
  class callback_chain;

  template<class Ret, class... Args>
  class callback_chain<Ret(Args...)> {
    using ret_t = std::optional<Ret>;
    using callback_t = ret_t(Args...);
    using func_t = function<callback_t>;

    std::vector<func_t> m_funcs {};

  public:
    template<class... FnArgs>
    void add(FnArgs &&... args) {
      m_funcs.emplace_back(std::forward<FnArgs>(args)...);
    }

    template<class... A>
    Ret operator()(A &&... args) {
      const auto fold = [&](ret_t ret, func_t & fn) {
        if (ret) return ret;
        return fn(std::forward<A>(args)...);
      };
      return std::accumulate(m_funcs.begin(), m_funcs.end(), ret_t {}, fold).value_or(Ret {});
    }
  };
}
