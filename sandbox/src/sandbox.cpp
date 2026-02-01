#include "VEGA.h"

#include <glm/vec3.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include <imgui/imgui.h>

#include "VEGA/Renderer/Shader.h"


class ExampleLayer : public VEGA::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f), m_Transform(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(VEGA::VertexArray::Create());


		float vertices[] = {
			-0.5f, -0.5f, 0.0f,1.0f,0.0f,1.0f,1.0f,
			 0.5f, -0.5f, 0.0f,1.0f,1.0f,0.0f,1.0f,
			 0.0f,  0.5f, 0.0f,1.0f,1.0f,1.0f,1.0f,

		};

		m_VertexBuffer.reset(VEGA::VertexBuffer::Create(vertices, sizeof(vertices)));


		VEGA::BufferLayout layout = {
				{VEGA::ShaderDataType::Float3,"a_Position"},
				{VEGA::ShaderDataType::Float4,"a_Color" }
		};


		/*BufferLayout layout2(layout);
		m_VertexBuffer->SetLayout(layout);*/

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);



		uint32_t indices[] = {
			0, 1, 2
		};

		m_IndexBuffer.reset(VEGA::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SqaureVA.reset(VEGA::VertexArray::Create());

		float vertiecsSquare[] = {
			-0.5f, -0.5f, 0.0f,0.0f,0.0f,
			 0.5f, -0.5f, 0.0f,1.0f,0.0f,
			 0.5f,  0.5f, 0.0f,1.0f,1.0f,
			-0.5f,  0.5f, 0.0f,0.0f,1.0f,
		};

		std::shared_ptr<VEGA::VertexBuffer> squareVB;
		squareVB.reset(VEGA::VertexBuffer::Create(vertiecsSquare, sizeof(vertiecsSquare)));

		VEGA::BufferLayout SVlayout = {
			{VEGA::ShaderDataType::Float3,"a_Position"},
			{VEGA::ShaderDataType::Float2,"a_TexCoord" }

		};

		squareVB->SetLayout(SVlayout);

		m_SqaureVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<VEGA::IndexBuffer> squareIB;
		squareIB.reset(VEGA::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SqaureVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
         #version 330 core
         layout( location = 0 ) in vec3 a_Position;
         layout( location = 1 ) in vec4 a_Color;         

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
         
         uniform mat4 u_ViewProjection;
         uniform mat4 u_Transform;         
 
         out vec3 v_Position; 
         out vec4 v_Color;         
 
         void main (){
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position =  u_ViewProjection * (u_Transform) * vec4(a_Position,1.0);
         }
        )";

		std::string fragmentSrc2 = R"(
         #version 330 core
         layout(location =0) out vec4 color;
          
         in vec3 v_Position;
         uniform vec4 v_Color; 


         void main (){
             color = vec4(v_Color);
         }
        )";


		std::string TexturevertexSrc = R"(
       #version 330 core

       layout(location = 0) in vec3 a_Position;
       layout(location = 1) in vec2 a_TexCoord;

       uniform mat4 u_ViewProjection;
       uniform mat4 u_Transform;

       out vec3 v_Position;
       out vec2 v_TexCoord;

       void main()
       {
          v_Position = a_Position;
          v_TexCoord = a_TexCoord;
          gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
       }

       )";

		std::string TexturefragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec2 v_TexCoord;

        uniform sampler2D u_Texture;

         void main()
         {
             color = texture(u_Texture, v_TexCoord);

         }
        )";

		auto textureShader = m_ShaderLibrary.Load("assests/shaders/Texture.glsl");
		m_Shader = (VEGA::Shader::Create("triangle", vertexSrc, fragmentSrc));
		m_Shader2 = (VEGA::Shader::Create("triangle",vertexSrc2, fragmentSrc2));
        
		

		m_Texture = (VEGA::Texture2D::Create("assests/textures/Lily.jpg"));
		m_TextureLogo = (VEGA::Texture2D::Create("assests/textures/VEGA.png"));
		
		std::dynamic_pointer_cast<VEGA::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<VEGA::OpenGLShader>(textureShader)->SetUniformInt("u_Texture", 0);
}

	void OnUpdate(VEGA::Timestep ts) override
	{
		//VG_TRACE("Delta time {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		float time = ts;

		if(VEGA::Input::IsKeyPressed(VG_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraSpeed * ts;
		}
		else if (VEGA::Input::IsKeyPressed(VG_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraSpeed * ts;
		}
		if (VEGA::Input::IsKeyPressed(VG_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraSpeed * ts;
		}
		else if (VEGA::Input::IsKeyPressed(VG_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraSpeed * ts;
		}

		if (VEGA::Input::IsKeyPressed(VG_KEY_A))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (VEGA::Input::IsKeyPressed(VG_KEY_D))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		if (VEGA::Input::IsKeyPressed(VG_KEY_J))
		{
			m_Transform.x += m_squareMoveSpeed * ts;
		}
		else if (VEGA::Input::IsKeyPressed(VG_KEY_L))
		{
			m_Transform.x -= m_squareMoveSpeed * ts;
		}
		if (VEGA::Input::IsKeyPressed(VG_KEY_I))
		{
			m_Transform.y += m_squareMoveSpeed * ts;
		}
		else if (VEGA::Input::IsKeyPressed(VG_KEY_K))
		{
			m_Transform.y -= m_squareMoveSpeed * ts;
		}
		// Poll events and swap buffers first so ImGui  callbacks update IO before NewFrame
		
		// Clear



		VEGA::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		VEGA::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		VEGA::Renderer::BeginScene(m_Camera);

		

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Transform);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	    
		glm::vec4 redColor = { 0.8f, 0.2f, 0.3f, 1.0f };	
		 

		/*VEGA::Material material = new VEGA::Material(Matrial_Shader2);
		VEGA::MaterialInstanceRef m1 new VEGA::MaterialInstance(material);

		squareMesh->SetMaterial(material);*/

		std::dynamic_pointer_cast<VEGA::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<VEGA::OpenGLShader>(m_Shader2)->SetUniformFloat4("v_Color", blueColor);



		for (int i = 0; i < 20; i++) {

			for(int j = 0; j < 20; j++) {
				glm::mat4 pos = glm::translate(glm::mat4(1.0f), glm::vec3(i * 0.11f, j * 0.11f, 0.0f));
				glm::mat4 transform = pos * scale;
				/*if(j % 2 == 0)
					m_Shader2->SetUniformFloat4("v_Color", redColor);
				else
					m_Shader2->SetUniformFloat4("v_Color", blueColor);*/
				VEGA::Renderer::Submit(m_Shader2, m_SqaureVA, transform);
			}

			auto textureShader = m_ShaderLibrary.Get("Texture");
			m_Texture->Bind();
			
			glm::mat4 logoTransform = glm::translate(glm::mat4(1.0f), m_Transform + glm::vec3(0.0f, 0.0f, 0.1f));
			VEGA::Renderer::Submit(textureShader, m_SqaureVA, logoTransform);


			m_TextureLogo->Bind();
			 logoTransform = glm::translate(glm::mat4(1.0f), m_Transform + glm::vec3(0.0f, 0.0f, 0.2f));
			VEGA::Renderer::Submit(textureShader, m_SqaureVA, logoTransform);
		/*	glm::mat4 pos = glm::translate(glm::mat4(1.0f), glm::vec3(i * 0.3f, 0.0f, 0.0f));
			glm::mat4 transform = pos * scale;
			VEGA::Renderer::Submit(m_Shader2, m_SqaureVA, transform);*/
		}
			/*VEGA::Renderer::Submit(m_Shader2, m_VertexArray);*/
		VEGA::Renderer::EndScene();
	}
	

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z);
		ImGui::Text("Camera Rotation: %.2f", m_CameraRotation);
		ImGui::Text("Square Position: (%.2f, %.2f, %.2f)", m_Transform.x, m_Transform.y, m_Transform.z);
		ImGui::ColorEdit3("Square Color", glm::value_ptr(blueColor));
		ImGui::End();
	}
private:
	VEGA::ShaderLibrary m_ShaderLibrary;
	VEGA::Ref<VEGA::Shader> m_Shader;
	VEGA::Ref<VEGA::VertexArray> m_VertexArray;
	VEGA::Ref<VEGA::VertexBuffer> m_VertexBuffer;
	VEGA::Ref<VEGA::IndexBuffer> m_IndexBuffer;
	
	VEGA::Ref<VEGA::Texture2D> m_Texture,m_TextureLogo;

	VEGA::Ref<VEGA::Shader> m_Shader2;
	VEGA::Ref<VEGA::VertexArray> m_SqaureVA;
	VEGA::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 120.0f;
	float m_CameraSpeed = 2.0f;
	glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec3 m_Transform;
	float m_squareMoveSpeed = 0.5f;
};

class Sandbox : public VEGA::Application
{
public:
	Sandbox()
		
	{
		PushLayer(new ExampleLayer);		
	}
	~Sandbox()
	{

	}
};


VEGA::Application* VEGA::CreateApplication()
{
	return new Sandbox();
}