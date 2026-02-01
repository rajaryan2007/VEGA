#include "vgpch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"

namespace VEGA
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VG_CORE_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}
		VG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		VG_CORE_ASSERT(!m_Shaders.contains(name), "Shader already exists!");
		m_Shaders[name] = shader;

	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		VG_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	VEGA::Ref<VEGA::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto& shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	VEGA::Ref<VEGA::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto& shader = Shader::Create(filepath);
		Add(name,shader);
		return shader;
	}
	
	VEGA::Ref<VEGA::Shader> ShaderLibrary::Get(const std::string& name)
	{
		VG_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}

}
