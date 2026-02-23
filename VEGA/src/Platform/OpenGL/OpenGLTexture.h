#pragma once

#include "VEGA/Renderer/Texture.h"

namespace VEGA {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(u32 width, u32 hight);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		

		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
		virtual void SetData(void* data, u32 size) override;

		virtual void Bind(u32 slot = 0) const override;
	private:
		u32 m_Width, m_Height;
		std::string m_Path;
		u32 m_RendererID;
		u32 m_InternalFormat, m_DataFormat;
	};
		
}
