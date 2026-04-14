#pragma once
#include "UHE.h"
#include "Panel/SceneHierachyPanel.h"
#include "UHE/Renderer/EditorCamera.h"
#include "Panel/ContentBrowserPanel.h"

namespace UHE
{
	class Editor : public Layer
	{
	public:
		Editor();
		virtual ~Editor() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		void OnEvent(Event& event) override;
        
		virtual void OnImGuiRender() override;
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	private:

		bool onKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
		void OpenScene(const std::filesystem::path& path);
	private:
		ShaderLibrary m_ShaderLibrary;


		Ref<Shader> m_Shader, textureShader;
		Ref<VertexArray> m_VertexArray;
		Ref<FrameBuffer> m_FrameBuffer;

		Ref<VertexArray > m_SqaureVA;
		Ref<Texture2D> m_TextureLOGO;
		Ref<Texture2D> m_TestTexture;
		Ref<Texture2D> m_TestSprite;

		Ref<SubTexture2D > m_Test;
		Ref<SubTexture2D> m_TestSubSprite;
		Ref<SubTexture2D> grass;
		Ref<SubTexture2D> water;
		Ref<SubTexture2D> dirt;

		Entity m_Square;
		Entity m_CameraEntity;
		Entity m_SecondCamera;

		Entity m_HoverdEntity;
		bool primaryCamera = false;
		EditorCamera m_EditorCamera;
		bool m_ViewPortFocused = false;
		bool m_ViewPortHover = false;
		
		OrthographicCameraContoroller m_CameraController;


		Ref<Scene> m_ActiveScene;

		

		glm::vec4 blueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec3 m_Transform;
		glm::vec4 redColor = { 0.8f, 0.2f, 0.3f, 1.0f };

		u32 m_mapWidth, m_mapHeight;

		glm::vec2 m_ViewPortSize;
		glm::vec2 m_ViewPortBounds[2];
		int m_GizmoType = -1;

		std::unordered_map<char, Ref<SubTexture2D>> Land;
		SceneHierarchyPanel m_SceneHireacyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
	};
}



