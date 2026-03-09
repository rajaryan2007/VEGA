#include "vgpch.h"
#include "SubTexture2D.h"

namespace VEGA {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		:m_Texture(texture)
	{
		m_TexCoords[0] = { min.x,min.y };
		m_TexCoords[1] = { max.x,min.y };
		m_TexCoords[2] = { max.x,max.y };
		m_TexCoords[3] = { min.x,max.y };

	}


	VEGA::Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2 cellsize,const glm::vec2& spriteSizes )
	{

		glm::vec2 min = { (coords.x * cellsize.x) / texture->GetWidth(), (coords.y * cellsize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + spriteSizes.x) * cellsize.x) / texture->GetWidth(),((coords.y + spriteSizes.y) * cellsize.y) / texture->GetHeight() };
		
		return CreateRef<SubTexture2D>(texture, min, max);

	}

}