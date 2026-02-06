#include "vgpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace VEGA {

   static GLenum ShaderTypeFromString(const std::string& type)
   {
   	if (type == "vertex")
   		return GL_VERTEX_SHADER;
   	if (type == "fragment" || type == "pixel")
   		return GL_FRAGMENT_SHADER;
   	VG_CORE_ASSERT(false, "Unknown shader type!");
   	return 0;
   }
}

void VEGA::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	GLuint program = glCreateProgram();
	std::array<GLuint,2> shaderIDs;
	int GLShaderIndex = 0;	

	for (auto& [type, source] : shaderSources)
	{
		GLuint shader = glCreateShader(type);

		const GLchar* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			std::vector<char> log(length);
			glGetShaderInfoLog(shader, length, &length, log.data());

			glDeleteShader(shader);
			VG_CORE_ERROR("Shader compile error: {0}", log.data());
			VG_CORE_ASSERT(false);
			return;
		}

		glAttachShader(program, shader);
		shaderIDs[GLShaderIndex++] = shader;
	}

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		std::vector<char> log(length);
		glGetProgramInfoLog(program, length, &length, log.data());

		glDeleteProgram(program);
		for (auto id : shaderIDs)
			glDeleteShader(id);

		VG_CORE_ERROR("Shader link error: {0}", log.data());
		VG_CORE_ASSERT(false);
		return;
	}

	for (auto id : shaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}

	m_RendererID = program;
}


VEGA::OpenGLShader::OpenGLShader(const std::string& filepath)
{
	std::string source = ReadFile(filepath);
	auto shaderSources = preProcess(source);
	Compile(shaderSources);
	// Option A: operate on m_Name (simple)
	auto lastSlash = filepath.find_last_of("/\\");
	if (lastSlash != std::string::npos)
	    m_Name = filepath.substr(lastSlash + 1); // "Texture.glsl"
	auto lastDot = m_Name.rfind('.');
	if (lastDot != std::string::npos)
	    m_Name = m_Name.substr(0, lastDot); // "Texture"
}

VEGA::OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) 
	: m_Name(name)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = fragmentSrc;
	Compile(sources);
	m_Name = name;
}


VEGA::OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
}

void VEGA::OpenGLShader::Bind() const
{
	glUseProgram(m_RendererID);

}

void VEGA::OpenGLShader::Unbind() const
{
	glUseProgram(0);
}

void VEGA::OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void VEGA::OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void VEGA::OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

std::string VEGA::OpenGLShader::ReadFile(const std::string& filepath)
{
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
	{
		VG_CORE_ERROR("Could not open file: {0}", filepath);
	}

	return result;
}

std::unordered_map<GLenum, std::string> VEGA::OpenGLShader::preProcess(const std::string& source)
{   
	std::unordered_map<GLenum, std::string> shaderSource;

	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken,0);
	
	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		VG_CORE_ASSERT(eol != std::string::npos, "Syntax error");
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		VG_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");
		size_t nextLinePos = source.find_first_not_of("\r\n", eol);
		
		VG_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
		
		pos = source.find(typeToken, nextLinePos);
		shaderSource[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
	}
  
	return shaderSource;

}

void VEGA::OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void VEGA::OpenGLShader::SetUniformInt(const std::string& name, int value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(location, value);
}

void VEGA::OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void VEGA::OpenGLShader::SetUniformVec3(const std::string& name, const glm::vec3& value)
{
	GLuint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

