#include "vgpch.h"

#include "Application.h"
#include "VEGA/Log.h"
#include "input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace VEGA{

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application* Application::s_instance = nullptr;


	Application::Application()
	{   
		VG_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);	
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//VG_CORE_TRACE("{0}", e.ToString());


		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
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
		// Poll events and swap buffers first so ImGui backend callbacks update IO before NewFrame
		m_Window->OnUpdate();
		// Clear
		glClearColor(1,1,0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();
		

	}

	};
	bool Application::OnWindowClose(WindowCloseEvent& e) 
	{   
		m_Running = false;
		return true;
	}
}
