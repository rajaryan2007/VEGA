#include "vgpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"


namespace VEGA
{
	Shader* Shader::Create(const std::string& vertexSrc,const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc,fragmentSrc);
		}
		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
