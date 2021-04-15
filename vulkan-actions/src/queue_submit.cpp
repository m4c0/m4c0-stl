#include "m4c0/vulkan/fence.hpp"
#include "m4c0/vulkan/queue.hpp"
#include "m4c0/vulkan/queue_submit.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/semaphore.hpp"

void m4c0::vulkan::actions::queue_submit::now() const {
  VkPipelineStageFlags stage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  VkSemaphore wait_semaphore = m_wait_semaphore->pointer();
  VkSemaphore signal_semaphore = m_signal_semaphore->pointer();

  VkSubmitInfo info {};
  info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  info.commandBufferCount = 1;
  info.pCommandBuffers = &m_cmd_buf;
  info.pWaitDstStageMask = &stage;
  info.waitSemaphoreCount = 1;
  info.pWaitSemaphores = &wait_semaphore;
  info.signalSemaphoreCount = 1;
  info.pSignalSemaphores = &signal_semaphore;
  details::safe_call(vkQueueSubmit, m_queue->pointer(), 1, &info, m_fence->pointer());
}
