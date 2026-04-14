#include "uhepch.h"
#include "Texture.h"

#include "UHE/Core/Core.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace UHE
{
	Ref<Texture2D> Texture2D::Create(const std::string & path) 
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		}
		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	
	}

	UHE::Ref<UHE::Texture2D> Texture2D::Create(unsigned int width, unsigned int height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width,height);
		}
		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

