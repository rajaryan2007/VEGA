#include "vgpch.h"
#include "OrthograpicCameraContoroller.h"
#include "VEGA/Renderer/OrthographicCamera.h"
#include "VEGA/Core/Timestep.h"
#include "VEGA/keyCodes.h"
#include "VEGA/Input.h"


VEGA::OrthographicCameraContoroller::OrthographicCameraContoroller( float aspectRatio, bool rotation /*= false*/)
	:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
{

	
}

void VEGA::OrthographicCameraContoroller::OnUpdate(Timestep ts)
{


	if (Input::IsKeyPressed(VG_KEY_LEFT))
	{
		m_CameraPosition.x += m_CameraTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(VG_KEY_RIGHT))
	{
		m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
	}
	if (Input::IsKeyPressed(VG_KEY_DOWN))
	{
		m_CameraPosition.y += m_CameraTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(VG_KEY_UP))
	{
		m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
	}

	

	if (m_Rotation) {

		if (Input::IsKeyPressed(VG_KEY_A))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VG_KEY_D))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		if (Input::IsKeyPressed(VG_KEY_J))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VG_KEY_L))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		if (Input::IsKeyPressed(VG_KEY_I))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}
		else if (Input::IsKeyPressed(VG_KEY_K))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		m_Camera.SetRotation(m_CameraRotation);
	}
	m_Camera.SetPosition(m_CameraPosition);

}

void VEGA::OrthographicCameraContoroller::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(VG_BIND_EVENT_FN(OrthographicCameraContoroller::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(VG_BIND_EVENT_FN(OrthographicCameraContoroller::OnWindowResized));
}

void VEGA::OrthographicCameraContoroller::Resize(float width, float height)
{

}

bool VEGA::OrthographicCameraContoroller::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool VEGA::OrthographicCameraContoroller::OnWindowResized(WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}
