#include "Application.h"
#include "VEGA/Log.h"
#include "VEGA/Events/ApplicationEvent.h"

namespace VEGA{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}


	
	
	
	void Application::Run() {
		
			
			
    WindowResizeEvent e(1200, 720);
	VG_TRACE(e.ToString());
	while (true);

	};
}
