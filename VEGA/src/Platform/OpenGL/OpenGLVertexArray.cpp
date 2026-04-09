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
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					element.Normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
		 	}

		    	default:  VG_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
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