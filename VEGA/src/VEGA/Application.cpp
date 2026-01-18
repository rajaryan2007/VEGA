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

		m_VertexArray.reset(VertexArray::Create());
		

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,1.0f,0.0f,1.0f,1.0f,
			 0.5f, -0.5f, 0.0f,1.0f,1.0f,0.0f,1.0f,
			 0.0f,  0.5f, 0.0f,1.0f,1.0f,1.0f,1.0f,
			
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));

		
        BufferLayout layout = {
				{ShaderDataType::Float3,"a_Position"},
				{ShaderDataType::Float4,"a_Color" }

	    };

		
		/*BufferLayout layout2(layout);
		m_VertexBuffer->SetLayout(layout);*/
		
	    m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		


		uint32_t indices[] = {
			0, 1, 2
		};       

		m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/ sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        
		m_SqaureVA.reset(VertexArray::Create());

		float vertiecsSquare[] = {
			-0.5f, -0.5f, 0.0f,0.2f,0.6f,1.3f,1.f,
			 0.5f, -0.5f, 0.0f,1.0f,0.0f,0.6f,1.0f,
			 0.5f,  0.5f, 0.0f,1.3f,0.0f,1.0f,1.0f,
			-0.5f,  0.5f, 0.0f,1.6f,0.8f,1.0f,1.0f,
		};

		std::shared_ptr<VertexBuffer> squareVB; 
		squareVB.reset(VertexBuffer::Create(vertiecsSquare, sizeof(vertiecsSquare)));

		BufferLayout SVlayout = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float4,"a_Color" }

		};

		squareVB->SetLayout(SVlayout);

		m_SqaureVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<IndexBuffer> squareIB; 
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SqaureVA->SetIndexBuffer(squareIB);


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

		std::string vertexSrc2 = R"(
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

		std::string fragmentSrc2 = R"(
         #version 330 core
         layout(location =0) out vec4 color;
          
         in vec3 v_Position;
         in vec4 v_Color; 
         void main (){
             color = vec4(v_Color);
         }
        )";

		m_Shader.reset(new Shader(vertexSrc,fragmentSrc));
		m_Shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
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

		m_Shader2->Bind();
		m_SqaureVA->Bind();
		glDrawElements(GL_TRIANGLES, m_SqaureVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
