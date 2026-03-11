#pragma once
#include "VEGA.h"

#include "ParticleSystem.h"

class Sandbox2D : public VEGA::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(VEGA::Timestep ts) override;
	void OnEvent(VEGA::Event& event) override;

	virtual void OnImGuiRender() override;

private:
	VEGA::ShaderLibrary m_ShaderLibrary;

	
	VEGA::Ref<VEGA::Shader> m_Shader, textureShader;
	VEGA::Ref<VEGA::VertexArray> m_VertexArray;
	VEGA::Ref<VEGA::FrameBuffer> m_FrameBuffer;

	VEGA::Ref<VEGA::VertexArray> m_SqaureVA;
	VEGA::Ref<VEGA::Texture2D> m_TextureLOGO;
	VEGA::Ref<VEGA::Texture2D> m_TestTexture;
	VEGA::Ref<VEGA::Texture2D> m_TestSprite;

	VEGA::Ref<VEGA::SubTexture2D> m_Test;
	VEGA::Ref<VEGA::SubTexture2D> m_TestSubSprite;
	VEGA::Ref<VEGA::SubTexture2D> grass;
	VEGA::Ref<VEGA::SubTexture2D> water;
	VEGA::Ref<VEGA::SubTexture2D> dirt;


	VEGA::OrthographicCameraContoroller m_CameraController;




	glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec3 m_Transform;
	glm::vec4 redColor = { 0.8f, 0.2f, 0.3f, 1.0f };
    
	u32 m_mapWidth, m_mapHeight;

	std::unordered_map<char, VEGA::Ref<VEGA::SubTexture2D>> Land;

	ParticleSystem m_ParticleSystem;
	ParticleProps m_ParticleProps;
};

