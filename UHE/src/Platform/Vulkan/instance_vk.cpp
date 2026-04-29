#include "uhepch.h"
#include "instance_vk.h"
#include <volk.h>
#include <GLFW/glfw3.h>

std::vector<const char*>validationLayers = { "VK_LAYER_KHRONOS_validation;" };
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

namespace UHE {

    instance_vk::instance_vk()
        : m_context(), m_instance(nullptr), m_debugMessenger(nullptr)
    {
        if (volkInitialize() != VK_SUCCESS) {
            throw std::runtime_error("Failed to initialize Volk!");
        }
        if (!glfwVulkanSupported()) {
            VG_CORE_ERROR("Vulkan is not supported on this system!");
        }
    }

    void instance_vk::initialize()
    {
        VG_PROFILE_FUNCTION();
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Unhuman Engine";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 3, 0);
        appInfo.pEngineName = "UHE Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        std::vector<const char*> requiredLayer;
        if (enableValidationLayers)
        {
            requiredLayer.assign(validationLayers.begin(), validationLayers.end());
        }   

        auto layerProperties = m_context.enumerateInstanceLayerProperties();
        if (std::ranges::any_of(requiredLayer, [&layerProperties](
            auto const& requiredLayer) {
                return std::ranges::none_of(
                    layerProperties, [requiredLayer](auto const& layerProperties) {
                        return strcmp(layerProperties.layerName, requiredLayer) == 0;
                    });
            }))
        {
            throw std::runtime_error("Validation layers requested, but not available!");
        }

        auto requiredExtensions = getRequiredExtensions();

        auto requiredExtensionsProperties = m_context.enumerateInstanceExtensionProperties();
        if (std::ranges::any_of(requiredExtensions, [&requiredExtensionsProperties](
            auto const& requiredExtension) {
                return std::ranges::none_of(
                    requiredExtensionsProperties, [requiredExtension](auto const& extensionProperties) {
                        return strcmp(extensionProperties.extensionName, requiredExtension) == 0;
                    });
                }))
        {
            throw std::runtime_error("Required extensions are not available!");
        }

        vk::InstanceCreateInfo createInfo{};
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledLayerCount = static_cast<uint32_t>(requiredLayer.size());

    }

    std::vector<const char*> instance_vk::getRequiredExtensions()
    {
        u32 glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers)
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }

    vk::Bool32 instance_vk::debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,vk::DebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,void *pUserData) 
    {

    }

    void instance_vk::cleanup() 
    {
	  VG_PROFILE_FUNCTION();
	
    }
  } // namespace UHE
