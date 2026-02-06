#include "vgpch.h"
#include "Renderer2D.h"
#include "VEGA/Log.h"
#include "VertexArray.h"
#include "Shader.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Platform/OpenGL/OpenGLShader.h"
#include "RenderCommand.h"

namespace VEGA {

	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		
		Ref<Shader> Shader;
	};

	static Renderer2DStorage* s_Data;


	void Renderer2D::Init()
	{  
		s_Data = new Renderer2DStorage();
		
		s_Data->VertexArray = (VEGA::VertexArray::Create());

		float vertiecsSquare[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<VEGA::VertexBuffer> squareVB;
		squareVB.reset(VEGA::VertexBuffer::Create(vertiecsSquare, sizeof(vertiecsSquare)));

		VEGA::BufferLayout SVlayout = {
			{VEGA::ShaderDataType::Float3,"a_Position"},


		};

		squareVB->SetLayout(SVlayout);

		s_Data->VertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<VEGA::IndexBuffer> squareIB;
		squareIB.reset(VEGA::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		s_Data->VertexArray->SetIndexBuffer(squareIB);

		s_Data->Shader = VEGA::Shader::Create("assests/shaders/flatSquare.glsl");

	}

	void Renderer2D::Shutdown()
	{
		
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		
		s_Data->Shader->Bind();
		s_Data->Shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		

	}

	void Renderer2D::EndScene()
	{
		
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		
		DrawQuad({ position.x,position.y,0.0f }, size, color);

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		
		s_Data->Shader->Bind();

		s_Data->Shader->SetFloat4("u_color", color);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		s_Data->Shader->SetMat4("u_Transform", transform);

		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);


	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		
	}
}

