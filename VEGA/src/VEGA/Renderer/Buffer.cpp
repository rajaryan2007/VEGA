#include "vgpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace VEGA {
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
