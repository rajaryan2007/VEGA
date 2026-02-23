#include "vgpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/glad.h>


namespace VEGA {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		VG_PROFILE_FUNCTION();
		int width, height, channels;
		unsigned char* data = nullptr;
		stbi_set_flip_vertically_on_load(1);
		{
			VG_PROFILE_FUNCTION("OpenGL Texture::OpenGL");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		VG_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		m_InternalFormat = 0, m_DataFormat = 0;
		if (channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
		}
		
		
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTextureSubImage2D(
			m_RendererID,
			0,
			0, 0,
			m_Width, m_Height,
			m_DataFormat,
			GL_UNSIGNED_BYTE,
			data
		);
		
		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(u32 width, u32 hight)
		: m_Width(width),m_Height(hight)
	{
		VG_PROFILE_FUNCTION();
		
		m_InternalFormat = GL_RGBA8, m_DataFormat = GL_RGBA;
		
		
		VG_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		//stbi_image_free(data);
	}

	void OpenGLTexture2D::SetData(void* data, u32 size)
	{   
		VG_PROFILE_FUNCTION();
		u32 bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		VG_CORE_ASSERT(size == m_Width * m_Height * bpp,"Data must be entire texture");

		glTextureSubImage2D(m_RendererID,0,0,0,m_Width,m_Height,m_DataFormat,GL_UNSIGNED_BYTE,data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		VG_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(u32 slot) const
	{
		VG_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
	}
}






