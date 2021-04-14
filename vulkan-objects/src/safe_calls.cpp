#include "m4c0/vulkan/safe_calls.hpp"

#include <sstream>

static auto build_message(VkResult res) {
  std::ostringstream msg {};
  msg << "Failure calling Vulkan: " << res;
  return msg.str();
}

void m4c0::vulkan::details::check(VkResult res) {
  if (res == VK_SUCCESS) return;

  throw std::runtime_error(build_message(res));
}
