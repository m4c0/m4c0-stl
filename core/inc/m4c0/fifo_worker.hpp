#pragma once

#include "m4c0/function.hpp"

#include <mutex>

namespace m4c0 {
  template<typename Param>
  class fifo_worker {
    using action = function<void(Param)>;

    std::mutex m_mutex {};
    std::vector<action> m_prev_q {};
    std::vector<action> m_cur_q {};
    std::vector<action> m_next_q {};

    void flip() {
      std::lock_guard lock { m_mutex };
      m_prev_q = std::move(m_cur_q);
      m_cur_q = std::move(m_next_q);
      m_next_q.clear();
    }

  public:
    void enqueue(action && a) {
      std::lock_guard lock { m_mutex };
      m_next_q.push_back(std::forward<action>(a));
    }
    void process(Param p) {
      flip();

      for (auto & q : m_cur_q) {
        q(p);
      }
    }
  };
}
