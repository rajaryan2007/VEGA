#pragma once

#include <glm/glm.hpp>
#include "VEGA/Renderer/Texture.h"


namespace VEGA{

	class VEGA_API SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
        
		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }
	   
		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2 cellsize, const glm::vec2& spriteSizes = { 1,1 });
		static Ref<SubTexture2D> CreateFromPixels(
			const Ref<Texture2D>& texture,
			glm::vec2 pixelPos,
			glm::vec2 pixelSize
		);
	private:
		Ref<Texture2D> m_Texture;
		
		glm::vec2 m_TexCoords[4];
	};

}


