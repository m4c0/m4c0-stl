#pragma once

#include "m4c0/vulkan/handle.hpp"

#include <cstdint>

using VkDeviceMemory = struct VkDeviceMemory_T *;

namespace m4c0::vulkan {
  class memory_requirements;
  class physical_device;

  struct device_memory : details::handle<VkDeviceMemory> {
    class map_guard {
      VkDeviceMemory m_handle;
      void * m_ptr;

      friend class device_memory;
      map_guard(VkDeviceMemory handle, std::uint64_t offset, std::uint64_t size);

    public:
      ~map_guard();

      map_guard(const map_guard &) = delete;
      map_guard(map_guard &&) = delete;
      map_guard & operator=(const map_guard &) = delete;
      map_guard & operator=(map_guard &&) = delete;

      template<class Tp>
      [[nodiscard]] Tp * pointer() noexcept {
        return static_cast<Tp *>(m_ptr);
      }
    };

    using handle::handle;
    [[nodiscard]] static device_memory create_host_memory(const physical_device * pd, const memory_requirements * mr);
    [[nodiscard]] static device_memory create_local_memory(const physical_device * pd, const memory_requirements * mr);

    [[nodiscard]] map_guard map_all();
    [[nodiscard]] map_guard map_from_beginning(std::uint64_t size);
    [[nodiscard]] map_guard map_with_offset_and_size(std::uint64_t offset, std::uint64_t size);
  };
}