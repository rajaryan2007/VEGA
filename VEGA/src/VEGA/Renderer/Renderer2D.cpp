#include "vgpch.h"
#include "Renderer2D.h"
#include "VEGA/Log.h"
#include "VertexArray.h"
#include "Shader.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Platform/OpenGL/OpenGLShader.h"
#include "VEGA/Renderer/Texture.h"

#include "RenderCommand.h"

namespace VEGA {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec4 Color;
	};

	struct Renderer2DData
	{   
		const u32 MaxQuads = 10000;
		const u32 MaxVertices = MaxQuads * 4;
		const u32 MaxIndices = MaxQuads * 6;

		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> VertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D > WhiteTexture;

		u32 QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData s_Data;

	
	void Renderer2D::Init()
	{
		VG_PROFILE_FUNCTION();

		s_Data.VertexArray = VertexArray::Create();

		// Allocate memory for the vertex buffer
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.VertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));


		BufferLayout SVlayout = {
	       {ShaderDataType::Float3, "a_Position"},
	       {ShaderDataType::Float2, "a_TexCoord"},
	       {ShaderDataType::Float4, "a_Color"}
		};

		s_Data.VertexBuffer->SetLayout(SVlayout);
		s_Data.VertexArray->AddVertexBuffer(s_Data.VertexBuffer);

		u32* quadIndices = new u32[s_Data.MaxIndices];

		for(u32 i = 0, offset = 0; i < s_Data.MaxIndices; i += 6, offset += 4)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			
		}
		
		
		std::shared_ptr<VEGA::IndexBuffer> squareIB;
		squareIB.reset(VEGA::IndexBuffer::Create(quadIndices, s_Data.MaxIndices ));
		
		s_Data.VertexArray->SetIndexBuffer(squareIB);
		delete[] quadIndices;
		u32 whitePixel = 0xffffffff;
		
		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		s_Data.WhiteTexture->SetData(&whitePixel,sizeof(u32));

		
		//s_Data->Shader = VEGA::Shader::Create("assests/shaders/flatSquare.glsl");
		s_Data.TextureShader = VEGA::Shader::Create("assests/shaders/Texture.glsl");

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);


	}


	void Renderer2D::Shutdown()
	{
		VG_PROFILE_FUNCTION();
		
		delete[] s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBufferBase = nullptr;
		s_Data.QuadVertexBufferPtr = nullptr;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		VG_PROFILE_FUNCTION();
	
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data.TextureShader->SetMat4("u_Transform", glm::mat4(1.0f));
		s_Data.TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.WhiteTexture->Bind();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::flush()
	{
		

		RenderCommand::DrawIndexed(s_Data.VertexArray, s_Data.QuadIndexCount);

	}

	void Renderer2D::EndScene()
	{
		VG_PROFILE_FUNCTION();
		u32 dataSize = (u32)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.VertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
		flush();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		VG_PROFILE_FUNCTION();
		
		DrawQuad({ position.x,position.y,0.0f }, size, color);

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		VG_PROFILE_FUNCTION();

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
	}

		
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor , const glm::vec4& tintColor)
	{
		VG_PROFILE_FUNCTION();
		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tiling_factor);
		texture->Bind();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
		
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		
		s_Data.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor , const glm::vec4& tintColor )
	{
		VG_PROFILE_FUNCTION();
		DrawQuad({ position.x ,position.y,0 }, size, texture,tiling_factor,tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{   
		
		VG_PROFILE_FUNCTION();
		DrawRotatedQuad({ position.x,position.y,0.0f }, size, rotation, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		VG_PROFILE_FUNCTION();
		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->TexCoord = {0.0f,0.0f};
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = {position.x + size.x , position.y,0.0f};
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f,0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x , position.y + size.y,0.0f };
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f,0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = {position.x ,position.y + size.y ,0.};
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f,0.0f };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
	/*	s_Data.TextureShader->SetFloat4("u_Color", color);
		s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f }) * glm::rotate(glm::mat4(1.0f),rotation, { 0.0f,0.0f,1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray);*/
		

	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, Ref<Texture2D>& texture, float tiling_factor , const glm::vec4& tintColor )
	{
		VG_PROFILE_FUNCTION();
		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tiling_factor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f }) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f,0.0f,1.0f });

		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tintColor )
	{
		VG_PROFILE_FUNCTION();
		DrawRotatedQuad({ position.x,position.y,0 }, size, rotation, texture,tiling_factor,tintColor);
	}
}

