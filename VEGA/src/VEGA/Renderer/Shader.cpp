#include "vgpch.h"
#include "Shader.h"
#include <filesystem>
#include <fstream>
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer.h"
#include "slang.h"

#include "slang-com-helper.h"

namespace fs = std::filesystem;
namespace VEGA
{

	void Shader::InitSlang()
	{
		


		Slang::ComPtr<slang::IGlobalSession> globalSession;
		createGlobalSession(globalSession.writeRef());

		slang::SessionDesc sessionDesc = {};

		// ---------------- SPIR-V ----------------
		slang::TargetDesc spirvTarget = {};
		spirvTarget.format = SLANG_SPIRV;
		spirvTarget.profile = globalSession->findProfile("spirv_1_5");

		// ---------------- GLSL ----------------
		slang::TargetDesc glslTarget = {};
		glslTarget.format = SLANG_GLSL;
		glslTarget.profile = globalSession->findProfile("glsl_450");

		targets.push_back(spirvTarget);
		targets.push_back(glslTarget);

		sessionDesc.targets = targets.data();
		sessionDesc.targetCount = static_cast<uint32_t>(targets.size());

		globalSession->createSession(sessionDesc, session.writeRef());
	}

	void Shader::compileShaderAndSave(const std::string& slangShaderPath)
	{
		fs::path p(slangShaderPath);
		std::string baseName = (p.parent_path() / p.stem()).string();
		Slang::ComPtr<slang::IModule> module;
		struct EntryPointInfo {
			const char* name;
			const char* suffix;
		};
	
		std::vector<EntryPointInfo> entryPoints = {
			{"vertexMain", ".vert"},
			{"fragmentMain", ".frag"}
		};

		for (const auto& ep : entryPoints) {
			Slang::ComPtr<slang::IEntryPoint> entryPoint;
			module->findEntryPointByName(ep.name, entryPoint.writeRef());

			if (!entryPoint)
				return;
			slang::IComponentType* components[] = { module, entryPoint };
			Slang::ComPtr<slang::IComponentType> program;

			session->createCompositeComponentType(components, 2, program.writeRef());

			Slang::ComPtr<slang::IComponentType> linkedProgram;
			program->link(linkedProgram.writeRef());

			// it will generate things like shader.slang 
			// shader.vert.glsl
			// shader.frag.glsl

			// for spirv
			Slang::ComPtr<slang::IBlob> spirvBlob;
			linkedProgram->getTargetCode(0, spirvBlob.writeRef(), nullptr);
			if (spirvBlob) {
				std::string outPath = baseName + ep.suffix + ".spv";
				std::ofstream out(outPath, std::ios::binary);
				out.write((char*)spirvBlob->getBufferPointer(), spirvBlob->getBufferSize());
			}

			// for glsl

			Slang::ComPtr<slang::IBlob> glslBlob;
			linkedProgram->getTargetCode(1, glslBlob.writeRef(), nullptr);
			if (glslBlob) {
				std::string outPath = baseName + ep.suffix + ".glsl";
				std::ofstream out(outPath);
				out.write((char*)glslBlob->getBufferPointer(), glslBlob->getBufferSize());
			}
		}
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

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		VG_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;

	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		VG_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}

    VEGA::Ref<VEGA::Shader> ShaderLibrary::Load(const std::string& filepath)
    {
					auto shader = Shader::Create(filepath);
					Add(shader);
					return shader;
    }

    VEGA::Ref<VEGA::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
					auto shader = Shader::Create(filepath);
					Add(name, shader);
					return shader;
    }

	//VEGA::Ref<VEGA::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	//{
	//	auto shader = Shader::Create(filepath);
	//	Add(name,shader);
	//	return shader;
	//}
	
	VEGA::Ref<VEGA::Shader> ShaderLibrary::Get(const std::string& name)
	{
		VG_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}

}
