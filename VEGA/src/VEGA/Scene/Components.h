#pragma once 
#include "vgpch.h"
#include "glm/glm.hpp"

namespace VEGA
{
	struct TramsformComponent
	{ 

        glm::mat4 Transform = glm::mat4{1.0f};

		TramsformComponent() = default;
		TramsformComponent(const glm::mat4& transform)
            : Transform(transform) {
        }

        operator const glm::mat4& () { return Transform; }
        operator const glm::mat4& () const { return Transform; }
		
	}; 

	struct SpriteRendererComponent
	{
		glm::vec4 Color{1.0f};
		
		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color){}

	};
}