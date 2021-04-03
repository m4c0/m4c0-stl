#include "m4c0/log.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "safe_calls.hpp"

#include <string_view>
#include <vector>
#include <volk.h>

using namespace m4c0::vulkan;

static std::vector<const char *> get_layers() {
  const char * dump_api_env = std::getenv("BSG_VULKAN_API_DUMP");
  const bool dump_api = (dump_api_env != nullptr) && (std::string_view { dump_api_env } == "1");
  if (dump_api) {
    m4c0::log::debug("API dump requested");
  }

  std::vector<const char *> res {};
  for (auto & lp : details::safe_enumerate<VkLayerProperties>(vkEnumerateInstanceLayerProperties)) {
    std::string_view layer_name { static_cast<const char *>(lp.layerName) };
    if (layer_name == "VK_LAYER_KHRONOS_validation") {
      res.push_back("VK_LAYER_KHRONOS_validation");
      m4c0::log::info("Enabling validation layer");
    }
    if (dump_api && layer_name == "VK_LAYER_LUNARG_api_dump") {
      res.push_back("VK_LAYER_LUNARG_api_dump");
      m4c0::log::info("Enabling API dump");
    }
  }
  return res;
}

static std::vector<const char *> get_extensions() {
  std::vector<const char *> res {};
  res.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
  res.push_back(M4C0_VULKAN_SURFACE_EXTENSION_NAME);

  for (auto & lp : details::safe_enumerate<VkExtensionProperties>(vkEnumerateInstanceExtensionProperties, nullptr)) {
    std::string_view ext_name { static_cast<const char *>(lp.extensionName) };
    if (ext_name == VK_EXT_DEBUG_UTILS_EXTENSION_NAME) {
      res.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
      m4c0::log::info("Enabling debug utils");
    }
  }
  return res;
}

static VkInstance create_instance(const char * app_name) {
  auto layers = get_layers();
  auto extensions = get_extensions();

  VkApplicationInfo app_info {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = app_name;
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // NOLINT(hicpp-signed-bitwise)
  app_info.pEngineName = "m4c0";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0); // NOLINT(hicpp-signed-bitwise)
  app_info.apiVersion = VK_API_VERSION_1_0;          // NOLINT(hicpp-signed-bitwise)

  VkInstanceCreateInfo create_info {};
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  create_info.enabledLayerCount = layers.size();
  create_info.ppEnabledLayerNames = layers.data();

  create_info.enabledExtensionCount = extensions.size();
  create_info.ppEnabledExtensionNames = extensions.data();

  return details::safe_create<VkInstance>(vkCreateInstance, &create_info);
}

instance instance::create_for_app(const char * app_name) {
  volkInitialize();

  VkInstance i = create_instance(app_name);
  volkLoadInstance(i);
  return instance { i };
}
template<>
void details::handle<VkInstance>::reset() {
  vkDestroyInstance(pointer(), nullptr);
}
