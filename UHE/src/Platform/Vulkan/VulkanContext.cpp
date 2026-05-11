#include <uhepch.h>
#include "VulkanContext.h"
#include <GLFW/glfw3.h>


namespace UHE {
  VkContext::VkContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle)
  {
    VG_PROFILE_FUNCTION();
    VG_CORE_ASSERT(windowHandle, "Window handle is null!");
  }

  void VkContext::Init() 
  {
      VG_PROFILE_FUNCTION(); 
      
  }

  void VkContext::SwapBuffers() 
  {
      VG_PROFILE_FUNCTION();
      VG_GPU_COLLECT;


  }
  } // namespace UHE


