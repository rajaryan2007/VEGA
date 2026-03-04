#include "vgpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace VEGA {
	OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top)
	{
		SetProjection(left, right, bottom, top);
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetProjection(f32 left, f32 right, f32 bottom, f32 top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


}