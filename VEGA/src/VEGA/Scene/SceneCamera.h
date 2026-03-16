#pragma once

#include "VEGA/Scene/Camera.h"

namespace VEGA {
class VEGA_API SceneCamera : public Camera {
public:
  SceneCamera() = default;
  virtual ~SceneCamera();

  void SetOrthographic(float size, float nearClip, float farClip);

  void SetViewportSize(u32 width, u32 height);

  float GetOrthographicSize() const { return m_OrhtographicSize; }
  void SetOrthographicSize(float size) {
    m_OrhtographicSize = size;
    RecalculateProjection();
  }

private:
  void RecalculateProjection();

private:
  float m_OrhtographicSize = 10.0f;
  float m_OthergraphicNear = -1.0f, m_OthergraphicFar = 1.0f;

  f32 m_AspactRatio = 0;
};
} // namespace VEGA
