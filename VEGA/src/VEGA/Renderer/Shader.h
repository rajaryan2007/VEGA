#pragma once
#include <string>
#include <glm/glm.hpp>
namespace VEGA {
	class Shader
	{
	public:
		Shader(const  std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
		void SetUniformInt(const std::string& name, int value);	
		void SetUniformFloat4(const std::string& name, const glm::vec4& value);
	private:
		uint32_t m_RendererID;
	};
}