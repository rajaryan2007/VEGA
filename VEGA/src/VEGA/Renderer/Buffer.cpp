#include "vgpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace VEGA {

	uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Float4: return 4 * 4;
		case ShaderDataType::Mat3:   return 4 * 3 * 3;
		case ShaderDataType::Mat4:   return 4 * 4 * 4;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 4 * 2;
		case ShaderDataType::Int3:   return 4 * 3;
		case ShaderDataType::Int4:   return 4 * 4;
		case ShaderDataType::Bool:   return 1;
		}
		VG_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) 
	{
		switch (Renderer::GetAPI()) 
		{
			case RendererAPI::None: 
				VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!"); 
				return nullptr;
#if VG_PLATFORM_WINDOWS   
			case RendererAPI::OpenGL: 
				return new OpenGLVertexBuffer(vertices, size);
#endif		
			default:
				VG_CORE_ASSERT(false, "Unknown RendererAPI!");
				return nullptr;
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:  VG_CORE_ASSERT(false, "Renderer::None i currently not supported!");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);

		}
		VG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
