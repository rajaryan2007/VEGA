#include <vgpch.h>

#include "Application.h"
#include "VEGA/Log.h"
#include "VEGA/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>


namespace VEGA{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}


	
	
	
	void Application::Run() {
		
			
			
    WindowResizeEvent e(1200, 720);
	if (e.IsInCategory(EventCategoryApplication))
	{
		VG_TRACE(e.ToString());
	}
	if (e.IsInCategory(EventCategoryInput))
	{
		VG_TRACE(e.ToString());
	}

	while (m_Running)
	{   
		glClearColor(1,1,0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		m_Window->OnUpdate();
	}

	};
}
