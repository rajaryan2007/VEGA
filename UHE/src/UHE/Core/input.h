#pragma once

#include "UHE/Core/Core.h"
#include <utility>

namespace UHE {

class UHE_API Input {
public:
  static bool IsKeyPressed(int keycode);

  static bool IsMouseButtonPressed(int button);
  static std::pair<float, float> GetMousePosition();
  static float GetMouseX();
  static float GetMouseY();
};

} // namespace UHE