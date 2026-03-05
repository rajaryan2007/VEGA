#pragma once
#include <glm/glm.hpp>
#include "VEGA/Events/Event.h"
#include "VEGA/Events/MouseEvent.h"
#include "VEGA/Renderer/OrthographicCamera.h"
#include "VEGA/Events/ApplicationEvent.h"





namespace VEGA {
	
	class OrthographicCameraBounds
	{
	public:
		f32 Left, Right, Bottom, Top;
		f32 GetWidth() const { return Right - Left; }
		f32 GetHeight() const { return Top - Bottom; }

	};
	

	class Timestep;
	class OrthographicCameraContoroller
	{
	public:
		OrthographicCameraContoroller( float aspectRatio, bool rotation = false);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; } // Moved to public access
		OrthographicCameraBounds GetBounds() const { return m_Bounds; } // Moved to public access

	private:
		void Resize(float width, float height);
		float GetZoomLevel() const { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	

	
	private:
	
		float m_AspectRatio;
		bool m_Rotation;
		float m_ZoomLevel = 1.0f;
		
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;

		

	};
}	