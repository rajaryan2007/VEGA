#pragma once
#include "Core.h"
#include "Window.h"
#include "VEGA/LayerStack.h"
#include "Events/Event.h"
#include "VEGA/Events/ApplicationEvent.h"
#include "VEGA/ImGui/ImGuiLayer.h"

#include "VEGA\Renderer\Shader.h"


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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		static Application* s_instance;
	};

	//T0 be define in class
	Application* CreateApplication();

}
