#include "vgpch.h"

#include "Application.h"
#include "VEGA/Log.h"
#include "input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace VEGA{

#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application* Application::s_instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case VEGA::ShaderDataType::Float:    return GL_FLOAT;
		case VEGA::ShaderDataType::Float2:   return GL_FLOAT;
		case VEGA::ShaderDataType::Float3:   return GL_FLOAT;
		case VEGA::ShaderDataType::Float4:   return GL_FLOAT;
		case VEGA::ShaderDataType::Mat3:     return GL_FLOAT;
		case VEGA::ShaderDataType::Mat4:     return GL_FLOAT;
		case VEGA::ShaderDataType::Int:      return GL_INT;
		case VEGA::ShaderDataType::Int2:     return GL_INT;
		case VEGA::ShaderDataType::Int3:     return GL_INT;
		case VEGA::ShaderDataType::Int4:     return GL_INT;
		case VEGA::ShaderDataType::Bool:     return GL_BOOL;
		}
		VG_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{   
		VG_CORE_ASSERT(!s_instance, "Application already exists!");
		s_instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);	

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,1.0f,0.0f,1.0f,1.0f,
			 0.5f, -0.5f, 0.0f,1.0f,1.0f,0.0f,1.0f,
			 0.0f,  0.5f, 0.0f,1.0f,1.0f,1.0f,1.0f,
			
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));

		{
			BufferLayout layout = {
				{ShaderDataType::Float3,"a_Position"},
				{ShaderDataType::Float4,"a_Color" }

			};

			m_VertexBuffer->SetLayout(layout);
		}
		/*BufferLayout layout2(layout);
		m_VertexBuffer->SetLayout(layout);*/
		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout )
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		
		
		uint32_t indices[] = {
			0, 1, 2
		};       

		m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/ sizeof(uint32_t)));
		
        
		std::string vertexSrc = R"(
         #version 330 core
         layout(location =0) in vec3 a_Position;
         layout(location =1) in vec4 a_Color;         

         out vec3 v_Position; 
         out vec4 v_Color;         
 
         void main (){
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = vec4(a_Position,1.0);
         }
        )";

		std::string fragmentSrc = R"(
         #version 330 core
         layout(location =0) out vec4 color;
          
         in vec3 v_Position;
         in vec4 v_Color; 
         void main (){
             color = vec4(v_Color);
         }
        )";
		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));
	
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

		m_Shader->Bind();
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
