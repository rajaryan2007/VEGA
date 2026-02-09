#include "vgpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

#include <glad/glad.h>


namespace VEGA {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
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

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t hight)
		: m_Width(width),m_Height(hight)
	{
		
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

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{   
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		VG_CORE_ASSERT(size == m_Width * m_Height * bpp,"Data must be entire texture");

		glTextureSubImage2D(m_RendererID,0,0,0,m_Width,m_Height,m_DataFormat,GL_UNSIGNED_BYTE,data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}






