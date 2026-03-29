#pragma once
#include "VEGA/Renderer/Texture.h"
#include "VEGA/Renderer2D/SubTexture2D.h"
#include <glm/glm.hpp>


namespace VEGA {
class SpriteAnimation {
public:
  SpriteAnimation() = default;

  void StartAnimation();
  void StopAnimation();

  void Tick(float deltaTime);

  Ref<SubTexture2D> GetCurrentFrame() const;

  // Data payload
  Ref<Texture2D> SpriteSheet;
  glm::vec2 FrameSize = {1.0f, 1.0f};
  int FrameCount = 1;
  float FrameDuration = 0.1f;

  bool Loop = true;
  bool Playing = false;

  int CurrentFrameIndex = 0;
  float Timer = 0.0f;
};
} // namespace VEGA
