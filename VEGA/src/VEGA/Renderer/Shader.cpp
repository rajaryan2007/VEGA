#include "vgpch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

VEGA::Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = (const GLchar*)vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
		
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(vertexShader);


		VG_CORE_ERROR("{0}", infoLog.data());
		VG_CORE_ASSERT(false, "VERTEX SHADER compilation failure!")
			return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = (const GLchar*)fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(fragmentShader);
		

		VG_CORE_ERROR("{0}", infoLog.data());
		VG_CORE_ASSERT(false, "Fragment SHADER compilation failure!")
			return;
	}

	m_RendererID = glCreateProgram();
	GLuint program = m_RendererID;
// Attach our shaders to our program
glAttachShader(program, vertexShader);
glAttachShader(program, fragmentShader);

// Link our program
glLinkProgram(program);

// Note the different functions here: glGetProgram* instead of glGetShader*.
GLint isLinked = 0;
glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
if (isLinked == GL_FALSE)
{
	GLint maxLength = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

	// The maxLength includes the NULL character
	std::vector<GLchar> infoLog(maxLength);
	glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
	
	// We don't need the program anymore.
	glDeleteProgram(program);
	// Don't leak shaders either.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Use the infoLog as you see fit.
	
	// In this simple program, we'll just leave
	return;
}

// Always detach shaders after a successful link.
glDetachShader(program, vertexShader);
glDetachShader(program, fragmentShader);

}

VEGA::Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}





void VEGA::Shader::Bind() const
{
	glUseProgram(m_RendererID);

}

void VEGA::Shader::Unbind() const
{
	glUseProgram(0);
}

void VEGA::Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void VEGA::Shader::SetUniformInt(const std::string& name, int value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(location, value);
}

void VEGA::Shader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}
