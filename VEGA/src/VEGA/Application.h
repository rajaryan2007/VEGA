#pragma once
#include "Core.h"
#include "Window.h"
#include "VEGA/LayerStack.h"
#include "Events/Event.h"
#include "VEGA/Events/ApplicationEvent.h"
#include "VEGA/ImGui/ImGuiLayer.h"

#include "VEGA/Renderer/Shader.h"
#include "VEGA/Renderer/Buffer.h"
#include "VEGA/Renderer/VertexArray.h"

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

		
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		std::shared_ptr<Shader> m_Shader2;
		std::shared_ptr<VertexArray> m_SqaureVA;

		static Application* s_instance;
	};

	//T0 be define in class
	Application* CreateApplication();

}
