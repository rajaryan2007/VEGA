#include "vgpch.h"
#include "OpenGLContext.h"	

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace VEGA {\

	static u32 s_GLFWWindowCount = 0;
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{   
		VG_PROFILE_FUNCTION();
		VG_CORE_ASSERT(windowHandle, "Window handle is null!");

	}
	void OpenGLContext::Init()
	{ 
		VG_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VG_CORE_ASSERT(status, "Failed to initialize Glad!");

		VG_CORE_INFO(
			"OpenGL Info: {0} {1}",
			reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
			reinterpret_cast<const char*>(glGetString(GL_RENDERER))
		);
		VG_CORE_INFO("  Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

	}
	void OpenGLContext::SwapBuffers()
	{
		VG_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}
}
