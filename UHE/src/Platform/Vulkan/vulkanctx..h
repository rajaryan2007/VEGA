#pragma once
#include <vulkan/vulkan_raii.hpp>

struct vulkanctx {
  vk::raii::Instance &instance;
  vk::raii::PhysicalDevice &physicalDevice;
  vk::raii::Device &device;
  vk::raii::SurfaceKHR &surface;
  vk::raii::SwapchainKHR &swapchain;
  vk::raii::CommandPool &commandPool;
  vk::raii::CommandBuffer &commandBuffer;
  vk::raii::Semaphore &imageAvailableSemaphore;
  vk::raii::Semaphore &renderFinishedSemaphore;
  vk::raii::Fence &inFlightFence;
  vk::raii::Fence &imagesInFlightFence;
  vk::raii::DescriptorSetLayout &descriptorSetLayout;
  vk::raii::PipelineLayout &pipelineLayout;
};
