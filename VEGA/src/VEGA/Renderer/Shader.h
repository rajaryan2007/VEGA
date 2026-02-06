#pragma once
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

namespace VEGA {
	class Shader
	{
	public:
		
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;



		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const  std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		uint32_t m_RendererID;
	};

	class ShaderLibrary
	{
	public:
		void Add(const  Ref<Shader>& shader);
		void Add(const  std::string& name, const Ref<Shader>& shader);




		Ref<Shader> Load(const  std::string& filepath);
		Ref<Shader> Load(const std::string& name, const  std::string& filepath);

		Ref<Shader> Get(const  std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}