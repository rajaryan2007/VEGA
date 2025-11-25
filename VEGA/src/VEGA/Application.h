#pragma once
#include "Core.h"
#include "Window.h"
#include "VEGA/LayerStack.h"
#include "Events/Event.h"
#include "VEGA/Events/ApplicationEvent.h"



namespace VEGA {


	class VEGA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<class Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_instance;
	};

	//T0 be define in class
	Application* CreateApplication();

}
