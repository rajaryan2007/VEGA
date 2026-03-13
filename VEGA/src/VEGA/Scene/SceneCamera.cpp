#include "vgpch.h"
#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace VEGA {


	SceneCamera::~SceneCamera()
	{
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrhtographicSize = size;
		m_OthergraphicNear = nearClip;
		m_OthergraphicFar = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(u32 width, u32 height)
	{
		m_AspactRatio = (float)width / (float)height;
		RecalculateProjection();
	}

    void SceneCamera::RecalculateProjection()
    {
        float orthoLeft = -m_OrhtographicSize * m_AspactRatio * 0.5f;
        float orthoRight = m_OrhtographicSize * m_AspactRatio * 0.5f;
        float orhtoBottom = -m_OrhtographicSize * 0.5f;
        float orthoTop = m_OrhtographicSize * 0.5f;

        m_Projection = glm::ortho(orthoLeft, orthoRight, orhtoBottom, orthoTop, m_OthergraphicNear, m_OthergraphicFar);
    }

}