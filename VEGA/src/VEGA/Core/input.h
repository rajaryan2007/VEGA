#pragma once

#include "VEGA/Core/Core.h"
#include <utility>

namespace VEGA {

class VEGA_API Input {
public:
  static bool IsKeyPressed(int keycode);

  static bool IsMouseButtonPressed(int button);
  static std::pair<float, float> GetMousePosition();
  static float GetMouseX();
  static float GetMouseY();
};

} // namespace VEGA