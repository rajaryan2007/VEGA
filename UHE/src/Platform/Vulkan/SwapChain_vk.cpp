#include "uhepch.h"
#include "SwapChain_vk.h"

namespace UHE {
   void VulkanSwapChain::createSwapChain(vk::raii::Device &device,
                                         vk::raii::PhysicalDevice &physicalDevice,
                                         vk::raii::SurfaceKHR &surface,
                                         GLFWwindow *window) {
     auto SurfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(*surface);
     swapChainExtent = chooseSwapExtent(SurfaceCapabilities, window);
     swapChainSurfaceFormat = chooseSwapSurfaceFormat(physicalDevice.getSurfaceFormatsKHR(*surface));
     auto SurfaceFormats = physicalDevice.getSurfaceFormatsKHR(*surface);



   }
   
   vk::Extent2D VulkanSwapChain::chooseSwapExtent(
       const vk::SurfaceCapabilitiesKHR &capabilities, GLFWwindow *window) {
     if (capabilities.currentExtent.width != 0xFFFFFFFF) {
       return capabilities.currentExtent;
     }
     i32 width, height;
   
     glfwGetFramebufferSize(window, &width, &height);
   
     return vk::Extent2D(std::clamp(static_cast<uint32_t>(width),
                                    capabilities.minImageExtent.width,
                                    capabilities.maxImageExtent.width),
                         std::clamp(static_cast<uint32_t>(height),
                                    capabilities.minImageExtent.height,
                                    capabilities.maxImageExtent.height));
   }
   
   vk::PresentModeKHR VulkanSwapChain::chooseSwapPresentMode(
       const std::vector<vk::PresentModeKHR> &availablePresentModes) {
     assert(std::ranges::any_of(availablePresentModes, [](auto presentMode) {
       return presentMode == vk::PresentModeKHR::eFifo;
     }));

     return std::ranges::any_of(availablePresentModes,
                                [](const vk::PresentModeKHR value) {
                                  return vk::PresentModeKHR::eMailbox == value;
                                })
                ? vk::PresentModeKHR::eMailbox
                : vk::PresentModeKHR::eFifo;
   }

   vk::SurfaceFormatKHR VulkanSwapChain::chooseSwapSurfaceFormat(
       const std::vector<vk::SurfaceFormatKHR> &availableFormats) 
   {
     assert(!availableFormats.empty());
     const auto formatIt =
         std::find_if(availableFormats.begin(), availableFormats.end(), [](const auto &availableFormat) {
                 return availableFormat.format == vk::Format::eB8G8R8A8Srgb &&
                        availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear;
     });
     return formatIt != availableFormats.end() ? *formatIt
                                               : availableFormats[0];
   }

   u32 VulkanSwapChain::ChooseSwapMinImage(vk::SurfaceCapabilitiesKHR const& surfaceCapabilites)
   { 
       auto minImageCount = std::max(3u, surfaceCapabilites.minImageCount);
       if ((0 < surfaceCapabilites.maxImageCount)
           && (minImageCount > surfaceCapabilites.maxImageCount))
       {
          minImageCount = surfaceCapabilites.maxImageCount;
       }

       return minImageCount;
   }

   vk::raii::ImageView VulkanSwapChain::


}


