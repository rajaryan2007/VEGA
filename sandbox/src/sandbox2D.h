#pragma once
#include "UHE.h"

#include "ParticleSystem.h"

#include <imgui/imgui.h>

class Sandbox2D : public UHE::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(UHE::Timestep ts) override;
	void OnEvent(UHE::Event& event) override;

	virtual void OnImGuiRender() override;

private:
	UHE::ShaderLibrary m_ShaderLibrary;

	
	UHE::Ref<UHE::Shader> m_Shader, textureShader;
	UHE::Ref<UHE::VertexArray> m_VertexArray;
	UHE::Ref<UHE::FrameBuffer> m_FrameBuffer;

	UHE::Ref<UHE::VertexArray> m_SqaureVA;
	UHE::Ref<UHE::Texture2D> m_TextureLOGO;
	UHE::Ref<UHE::Texture2D> m_TestTexture;
	UHE::Ref<UHE::Texture2D> m_TestSprite;

	UHE::Ref<UHE::SubTexture2D> m_Test;
	UHE::Ref<UHE::SubTexture2D> m_TestSubSprite;
	UHE::Ref<UHE::SubTexture2D> grass;
	UHE::Ref<UHE::SubTexture2D> water;
	UHE::Ref<UHE::SubTexture2D> dirt;


	UHE::OrthographicCameraContoroller m_CameraController;




	glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec3 m_Transform;
	glm::vec4 redColor = { 0.8f, 0.2f, 0.3f, 1.0f };
    
	u32 m_mapWidth, m_mapHeight;

	std::unordered_map<char, UHE::Ref<UHE::SubTexture2D>> Land;

	ParticleSystem m_ParticleSystem;
	ParticleProps m_ParticleProps;
};

