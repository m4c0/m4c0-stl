#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/semaphore.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "m4c0/vulkan/surface_format.hpp"
#include "m4c0/vulkan/swapchain.hpp"
#include "safe_calls.hpp"

using namespace m4c0::vulkan;

static constexpr auto get_min_image_count(const VkSurfaceCapabilitiesKHR & cap) {
  auto count = cap.minImageCount + 1;
  if ((cap.maxImageCount > 0) && (count > cap.maxImageCount)) {
    return cap.maxImageCount;
  }
  return count;
}

static VkSurfaceCapabilitiesKHR get_surface_capabilities(const physical_device * pd, const surface * surf) {
  VkSurfaceCapabilitiesKHR cap {};
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pd->pointer(), surf->pointer(), &cap);
  return cap;
}

static VkPresentModeKHR get_present_mode(const physical_device * pd, const surface * surf) {
  auto modes = details::safe_enumerate<VkPresentModeKHR>(
      vkGetPhysicalDeviceSurfacePresentModesKHR,
      pd->pointer(),
      surf->pointer());
  auto it = std::find(std::begin(modes), std::end(modes), VK_PRESENT_MODE_MAILBOX_KHR);
  return (it == std::end(modes) ? VK_PRESENT_MODE_FIFO_KHR : VK_PRESENT_MODE_MAILBOX_KHR);
}

swapchain swapchain::best_for(const physical_device * pd, const surface * s, unsigned int w, unsigned int h) {
  const auto cap = get_surface_capabilities(pd, s);
  const auto present_mode = get_present_mode(pd, s);
  const auto format = surface_format::best_from_device_and_surface(pd, s);

  VkSwapchainCreateInfoKHR info {};
  info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  info.clipped = VK_TRUE;
  info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  info.imageArrayLayers = 1;
  info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // TODO: check if graphics_q != present_q
  info.imageExtent = { w, h };
  info.presentMode = present_mode;
  info.surface = s->pointer();
  info.minImageCount = get_min_image_count(cap);
  info.preTransform = cap.currentTransform;
  info.imageColorSpace = format.pointer()->colorSpace;
  info.imageFormat = format.pointer()->format;
  return swapchain { details::safe_create_d<VkSwapchainKHR>(vkCreateSwapchainKHR, &info) };
}

template<>
void details::handle<VkSwapchainKHR>::reset() {
  vkDestroySwapchainKHR(loader::get_device(), pointer(), nullptr);
}

std::vector<VkImage> swapchain::get_images() const {
  return details::safe_enumerate<VkImage>(vkGetSwapchainImagesKHR, loader::get_device(), pointer());
}

unsigned swapchain::acquire_next_image(const semaphore * sem) const {
  constexpr const auto timeout = std::numeric_limits<uint64_t>::max();

  std::uint32_t index {};
  switch (vkAcquireNextImageKHR(loader::get_device(), pointer(), timeout, sem->pointer(), VK_NULL_HANDLE, &index)) {
  case VK_ERROR_OUT_OF_DATE_KHR:
    throw out_of_date_error();
  case VK_SUCCESS:
  case VK_SUBOPTIMAL_KHR:
    return index;
  default:
    throw std::runtime_error("Failed to acquire image from swap chain");
  }
}
