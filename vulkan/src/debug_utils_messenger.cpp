#include "m4c0/log.hpp"
#include "m4c0/vulkan/debug_utils_messenger.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "safe_calls.hpp"

#include <string>

using namespace m4c0::vulkan;

static std::string message_type(VkDebugUtilsMessageTypeFlagsEXT type) {
  switch (type) {
  case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
    return "[vulkan] [general]";
  case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
    return "[vulkan] [performance]";
  case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
    return "[vulkan] [validation]";
  default:
    return "[vulkan] [unknown]";
  }
}

static auto message(VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT * data) {
  return message_type(type) + " " + data->pMessage;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT * data,
    [[maybe_unused]] void * user_data) {

  switch (severity) {
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
    m4c0::log::error(message(type, data).c_str());
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
    m4c0::log::warning(message(type, data).c_str());
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
    m4c0::log::info(message(type, data).c_str());
    break;
  case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
    m4c0::log::debug(message(type, data).c_str());
    break;
  default:
    m4c0::log::info(message(type, data).c_str());
    break;
  }
  return VK_FALSE;
}

debug_utils_messenger debug_utils_messenger::create() {
  VkDebugUtilsMessengerCreateInfoEXT info {};
  info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  info.pfnUserCallback = debug_callback;
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
                       | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
                       | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
                   | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  VkInstance instance = volkGetLoadedInstance();
  return debug_utils_messenger {
    details::safe_create<VkDebugUtilsMessengerEXT>(vkCreateDebugUtilsMessengerEXT, instance, &info)
  };
}
template<>
void details::handle<VkDebugUtilsMessengerEXT>::reset() {
  vkDestroyDebugUtilsMessengerEXT(loader::get_instance(), pointer(), nullptr);
}
