#pragma once

#include <glm/glm.hpp>

namespace UHE {

	class UHE_API OrthographicCamera
	{
	public:
		OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top);
		
		void SetProjection(f32 left, f32 right, f32 bottom, f32 top);
		
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		const glm::vec3& GetPosition() const { return m_Position; }
		
		void SetRotation(f32 rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
		f32 GetRotation() const { return m_Rotation; }
	
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		f32 m_Rotation = 0.0f;
	};
}