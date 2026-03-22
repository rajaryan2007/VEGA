#pragma once
#include "entt.hpp"
#include "VEGA/Renderer2D/SubTexture2D.h"

namespace VEGA {
	class SpriteAnimation {
	public:
		SpriteAnimation();
		void StartAnimation(std::vector<SubTexture2D> spriteTextureArr);
		void StopAnimation();

	private:
		u32 FrameTime;
		u32 LastFrame;
		std::vector<SubTexture2D> SpriteTextureArr;
	};
}

