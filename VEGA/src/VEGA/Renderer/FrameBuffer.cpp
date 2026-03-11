#include "vgpch.h"
#include "FrameBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/FrameBufferOpenGL.h"

namespace VEGA
{

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
#if VG_PLATFORM_WINDOWS   
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(spec);
#endif		
		default:
			VG_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
		return nullptr;
	};


}
