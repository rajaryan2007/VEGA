#pragma once
#include <vulkan/vulkan_raii.hpp>

namespace UHE {
   class VulkanImageView {
   public: 
	   VulkanImageView() = default;
       VulkanImageView(const VulkanImageView &) = delete;
       VulkanImageView &operator=(const VulkanImageView &) = delete;

   private:

   };
}
