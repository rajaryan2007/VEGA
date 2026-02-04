#pragma once
#include "Core.h"
#include "Window.h"
#include "VEGA/LayerStack.h"
#include "Events/Event.h"
#include "VEGA/Events/ApplicationEvent.h"
#include "VEGA/ImGui/ImGuiLayer.h"
#include "VEGA/Core/Timestep.h"


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

		//bool OnWindowResize(WindowResizeEvent& e);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);


		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		
		

		
		static Application* s_instance;
	};

	//T0 be define in class
	Application* CreateApplication();

}
