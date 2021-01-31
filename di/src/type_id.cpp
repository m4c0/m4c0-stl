#include "m4c0/di/type_id.hpp"

#include <atomic>

int m4c0::di::type_id::new_id() {
  static std::atomic<int> m_last_id { 0 };
  return ++m_last_id;
}
