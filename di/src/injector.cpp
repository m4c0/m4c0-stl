#include "m4c0/di.hpp"
#include "m4c0/di/instance.hpp"
#include "m4c0/di/type_map.hpp"

#include <vector>

using namespace m4c0::di;

namespace {
  class linked_instance : public instance {
    linked_instance * m_next {};

  public:
    linked_instance() = default;
    linked_instance(void * ptr, void (*deleter)(void *), linked_instance * next)
      : instance(ptr, deleter)
      , m_next(next) {
    }

    [[nodiscard]] constexpr linked_instance * next() const noexcept {
      return m_next;
    }
  };
}

class injector::data {
  type_map<linked_instance> m_map {};
  std::vector<char> m_buffer {};
  linked_instance * m_top {};

public:
  explicit data(unsigned size) {
    m_buffer.reserve(size);
  }
  ~data() {
    cleanup();
  }
  data(data &&) = default;
  data(const data &) = delete;
  data & operator=(data &&) = default;
  data & operator=(const data &) = delete;

  void cleanup() {
    while (m_top != nullptr) {
      auto * next = m_top->next();
      *m_top = {};
      m_top = next;
    }
  }

  void put(int id, void * ptr, void (*deleter)(void *)) {
    m_map.put(id, linked_instance { ptr, deleter, m_top });
    m_top = &m_map.find(id)->second;
  }

  [[nodiscard]] void * get_ptr(unsigned loc) {
    return &m_buffer[loc];
  }

  [[nodiscard]] void * raw_get(int id) const {
    auto it = m_map.find(id);
    if (it == m_map.end()) {
      return nullptr;
    }
    return it->second.get();
  }
};

injector::injector(unsigned size, injector * p) : m_data(), m_parent(p) {
  m_data.make_new(size);
}

void injector::reset() noexcept {
  if (m_data) m_data->cleanup();
}

void * injector::get_ptr(unsigned loc) {
  return m_data->get_ptr(loc);
}

void injector::put(int id, void * ptr, void (*deleter)(void *)) {
  m_data->put(id, ptr, deleter);
}

void * injector::raw_get(int id) const {
  void * ptr = m_data->raw_get(id);
  if (ptr != nullptr) {
    return ptr;
  }
  if (m_parent == nullptr) {
    throw std::runtime_error("missing dependency");
  }
  return m_parent->raw_get(id);
}
