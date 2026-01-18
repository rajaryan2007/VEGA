#include "vgpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>



namespace VEGA {

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

    OpenGLVertexArray::OpenGLVertexArray() 
	{
		glGenVertexArrays(1, &m_RendererID);
	}
   
	OpenGLVertexArray::~OpenGLVertexArray() 
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const 
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const 
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) 
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		VG_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) 
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}