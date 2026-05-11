#pragma once
#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

namespace UHE {
  class VulkanSwapChain {
   private:
     VulkanSwapChain() = default;
     VulkanSwapChain(const VulkanSwapChain &) = delete;
     VulkanSwapChain &operator=(const VulkanSwapChain &) = delete;
     void createSwapChain(vk::raii::Device &device,
                          vk::raii::PhysicalDevice &physicalDevice,
                          vk::raii::SurfaceKHR &surface, GLFWwindow *window);
     
     void createImageViews();
     void cleanupSwapChain();

     vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR &capabilities,
                                   GLFWwindow *window);
     
     u32 chooseSwapMinImageCount(
         vk::SurfaceCapabilitiesKHR const &surfaceCapablities);

     vk::SurfaceFormatKHR chooseSwapSurfaceFormat(
         const std::vector<vk::SurfaceFormatKHR> &availableFormats);
     
     vk::PresentModeKHR chooseSwapPresentMode(
         const std::vector<vk::PresentModeKHR> &availablePresentModes);
     
     u32 ChooseSwapMinImage(vk::SurfaceCapabilitiesKHR const &surfaceCapabilites);
     
     private:
     vk::raii::SwapchainKHR           swapChain = nullptr;
     std::vector<vk::Image>           swapChainImages;
     vk::SurfaceFormatKHR             swapChainSurfaceFormat;
     vk::Extent2D                     swapChainExtent;
     std::vector<vk::raii::ImageView> swapChainImageViews;
     vk::raii::Sampler                textureSampler = nullptr;
     vk::raii::ImageView              textureImageView = nullptr;
  };

} // namespace UHE