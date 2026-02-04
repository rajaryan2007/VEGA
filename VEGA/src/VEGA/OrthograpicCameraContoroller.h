#pragma once
#include <glm/glm.hpp>
#include "VEGA/Events/Event.h"
#include "VEGA/Events/MouseEvent.h"
#include "VEGA/Renderer/OrthographicCamera.h"
#include "VEGA/Events/ApplicationEvent.h"





namespace VEGA {
	
	class Timestep;
	class OrthographicCameraContoroller
	{
	public:
		OrthographicCameraContoroller( float aspectRatio, bool rotation = false);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; } // Moved to public access


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
		OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;

		

	};
}	