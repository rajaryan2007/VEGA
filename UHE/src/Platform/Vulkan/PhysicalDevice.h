#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace UHE {
   class PhysicalDevice {
   public:
     PhysicalDevice() = default;
     PhysicalDevice(const PhysicalDevice &) = delete;
     PhysicalDevice &operator=(const PhysicalDevice &) = delete;
   
     void initPhysicalDevice();
   
   private:
     vk::raii::PhysicalDevice m_physicalDevice;
   };
} // namespace UHE