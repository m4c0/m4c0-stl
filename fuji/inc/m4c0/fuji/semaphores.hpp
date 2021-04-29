#pragma once

#include "m4c0/vulkan/typed_semaphore.hpp"

namespace m4c0::fuji {
  struct image_available_semaphore : public vulkan::tools::typed_semaphore<image_available_semaphore> {};
  struct render_finished_semaphore : public vulkan::tools::typed_semaphore<render_finished_semaphore> {};
}
