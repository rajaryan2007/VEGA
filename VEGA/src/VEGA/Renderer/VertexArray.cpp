#include "vgpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"


namespace VEGA
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}
		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
