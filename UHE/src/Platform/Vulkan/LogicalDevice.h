#pragma once
#define  VK_NO_PROTOTYPES
#include <vulkan/vulkan_raii.hpp>
#include <vk_mem_alloc.h>
#include <volk/volk.h>

namespace UHE {
  class VkLogicalDevice {
    VkLogicalDevice() = default;
    VkLogicalDevice(const VkLogicalDevice &) = delete;
    VkLogicalDevice &operator=(const VkLogicalDevice &) = delete;

    void initialize(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    void cleanup();

   public:
};
}

