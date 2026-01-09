#include "vgpch.h"
#include "OpenGLContext.h"	

#include <GLFW/glfw3.h>
#include "Glad/glad.h"	

namespace VEGA {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		VG_CORE_ASSERT(windowHandle, "Window handle is null!");

	}
	void OpenGLContext::Init()
	{ 
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VG_CORE_ASSERT(status, "Failed to initialize Glad!");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
