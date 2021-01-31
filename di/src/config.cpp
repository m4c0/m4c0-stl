#include "m4c0/di.hpp"
#include "m4c0/di/type_map.hpp"

#include <span>
#include <unordered_set>
#include <vector>

using namespace m4c0::di;

struct config::node_info {
  enum class mark { UNMARKED, TEMP, PERM };

  mark m_mark;
  init_fn_t m_init;
  bool m_has_init { false };
  unsigned m_loc;
  std::unordered_set<int> m_deps {};
};

struct config::graph : public type_map<node_info> {
  void toposort_visit_node(int node_id, std::unordered_set<int> * unmarked_nodes, std::vector<node_info *> * output);
};

static auto pad(unsigned value, unsigned align) {
  auto mod = value % align;
  if (mod == 0) return value;
  return value + (align - mod);
}

config::config() : m_graph() {
  m_graph.make_new();
}

void config::add_node(init_fn_t && fn, int tp, std::span<int> deps, unsigned size, unsigned align) {
  node_info & node = m_graph->get(tp);
  node.m_has_init = true;
  node.m_init = std::move(fn);
  node.m_loc = pad(m_size, align);
  for (int dep : deps) {
    node.m_deps.insert(dep);
  }
  m_size = node.m_loc + size;
}

injector config::build_injector(injector * parent) {
  std::unordered_set<int> unmarked_nodes {};
  for (auto & node : *m_graph) {
    node.second.m_mark = node_info::mark::UNMARKED;
    unmarked_nodes.insert(node.first);
  }

  std::vector<node_info *> inits {};
  while (!unmarked_nodes.empty()) {
    int node_id = *unmarked_nodes.begin();
    m_graph->toposort_visit_node(node_id, &unmarked_nodes, &inits);
  }

  injector i { m_size, parent };
  for (auto * node : inits) {
    node->m_init(i, node->m_loc);
  }
  return std::move(i);
}

void config::graph::toposort_visit_node(
    int node_id,
    std::unordered_set<int> * unmarked_nodes,
    std::vector<node_info *> * output) {
  node_info & info = get(node_id);
  switch (info.m_mark) {
  case node_info::mark::TEMP:
    throw std::runtime_error("cyclic dependency found");
  case node_info::mark::UNMARKED:
    unmarked_nodes->erase(node_id);

    info.m_mark = node_info::mark::TEMP;
    for (int dep : info.m_deps) {
      toposort_visit_node(dep, unmarked_nodes, output);
    }
    if (info.m_has_init) {
      output->push_back(&info);
    }
    info.m_mark = node_info::mark::PERM;
    break;
  case node_info::mark::PERM:
    break;
  }
}
