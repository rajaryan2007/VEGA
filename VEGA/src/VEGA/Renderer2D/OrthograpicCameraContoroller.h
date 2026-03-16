#pragma once
#include "VEGA/Events/ApplicationEvent.h"
#include "VEGA/Events/Event.h"
#include "VEGA/Events/MouseEvent.h"
#include "VEGA/Renderer2D/OrthographicCamera.h"
#include <glm/glm.hpp>

namespace VEGA {

class VEGA_API OrthographicCameraBounds {
public:
  f32 Left, Right, Bottom, Top;
  f32 GetWidth() const { return Right - Left; }
  f32 GetHeight() const { return Top - Bottom; }
};

class Timestep;
class VEGA_API OrthographicCameraContoroller {
public:
  OrthographicCameraContoroller(f32 aspectRatio, bool rotation = false);
  void OnUpdate(Timestep ts);
  void OnEvent(Event &e);

  void OnResize(f32 width, u32 height);

  OrthographicCamera &GetCamera() { return m_Camera; } // Moved to public access
  OrthographicCameraBounds GetBounds() const {
    return m_Bounds;
  } // Moved to public access
  void SetZoomLevel(f32 level) {
    m_ZoomLevel = level;
    CalculateView();
  }

private:
  f32 GetZoomLevel() const { return m_ZoomLevel; }

private:
  void CalculateView();

  bool OnMouseScrolled(MouseScrolledEvent &e);
  bool OnWindowResized(WindowResizeEvent &e);

private:
  f32 m_AspectRatio;
  bool m_Rotation;
  f32 m_ZoomLevel = 1.0f;

  OrthographicCameraBounds m_Bounds;
  OrthographicCamera m_Camera;
  glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
  f32 m_CameraRotation = 0.0f;
  f32 m_CameraTranslationSpeed = 5.0f;
  f32 m_CameraRotationSpeed = 180.0f;
};
} // namespace VEGA