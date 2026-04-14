#pragma once

#include "UHE/Renderer/Texture.h"

namespace UHE {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(u32 width, u32 hight);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		


		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
		virtual void SetData(void* data, u32 size) override;
        
		virtual u32 GetRendererID() const override { return m_RendererID; }

		virtual void Bind(u32 slot = 0) const override;

		// Change the parameter type of operator== from 'const Texture2D&' to 'const Texture&' to match the base class
		virtual bool operator==(const Texture& other)const override
		{
			return m_RendererID == ((const OpenGLTexture2D&)other).m_RendererID;
		};
	private:
		u32 m_Width, m_Height;
		std::string m_Path;
		u32 m_RendererID;
		u32 m_InternalFormat, m_DataFormat;
	};
		
}
