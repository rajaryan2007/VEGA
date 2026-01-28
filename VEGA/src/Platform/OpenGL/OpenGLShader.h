#pragma once
#include <string>
#include <glm/glm.hpp>

#include "VEGA/Renderer/Shader.h"

namespace VEGA {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const  std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
		void SetUniformInt(const std::string& name, int value);
		void SetUniformFloat4(const std::string& name, const glm::vec4& value);
		void SetUniformVec3(const std::string& name, const glm::vec3& value);
	private:
		uint32_t m_RendererID;
	};
}