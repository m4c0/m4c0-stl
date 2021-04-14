#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/out_of_date_error.hpp"
#include "m4c0/vulkan/queue.hpp"
#include "m4c0/vulkan/queue_present.hpp"
#include "m4c0/vulkan/semaphore.hpp"
#include "m4c0/vulkan/swapchain.hpp"

#include <stdexcept>

void m4c0::vulkan::actions::queue_present::now() const {
  VkSwapchainKHR swapchain = m_swapchain->pointer();
  VkSemaphore wait_semaphore = m_semaphore->pointer();

  VkPresentInfoKHR info {};
  info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  info.waitSemaphoreCount = 1;
  info.pWaitSemaphores = &wait_semaphore;
  info.swapchainCount = 1;
  info.pSwapchains = &swapchain;
  info.pImageIndices = &m_image_index;

  switch (vkQueuePresentKHR(m_present_queue->pointer(), &info)) {
  case VK_ERROR_OUT_OF_DATE_KHR:
  case VK_SUBOPTIMAL_KHR:
    throw out_of_date_error();
  case VK_SUCCESS:
    return;
  default:
    throw std::runtime_error("Unknown error presenting Vulkan queue");
  }
}
