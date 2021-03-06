#pragma once

#include "m4c0/function.hpp"

#include <mutex>
#include <vector>

namespace m4c0 {
  template<typename... Param>
  class fifo_worker {
    using action = function<void(Param...)>;

    std::mutex m_current_mutex {};
    std::mutex m_flip_mutex {};
    std::vector<action> m_prev_q {};
    std::vector<action> m_cur_q {};
    std::vector<action> m_next_q {};

    void flip() {
      std::lock_guard lock { m_flip_mutex };
      m_prev_q = std::move(m_cur_q);
      m_cur_q = std::move(m_next_q);
      m_next_q.clear();
    }

  public:
    void enqueue(action && a) {
      std::lock_guard lock { m_flip_mutex };
      m_next_q.push_back(std::forward<action>(a));
    }
    template<class... Args>
    void process(Args &&... p) {
      flip();

      std::lock_guard lock { m_current_mutex };
      for (auto & q : m_cur_q) {
        q(std::forward<Args>(p)...);
      }
    }
    void reset() {
      std::lock_guard lock1 { m_flip_mutex };
      std::lock_guard lock2 { m_current_mutex };
      m_prev_q.clear();
      m_cur_q.clear();
      m_next_q.clear();
    }
  };
}
