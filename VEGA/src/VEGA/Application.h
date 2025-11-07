#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"


namespace VEGA {


	class VEGA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<class Window> m_Window;
		bool m_Running = true;
	};

	//T0 be define in class
	Application* CreateApplication();

}
