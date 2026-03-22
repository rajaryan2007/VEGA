#include "SceneHierachyPanel.h"
#include "VEGA/Scene/Components.h"
#include "glm/trigonometric.hpp"
#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "imgui/imgui_internal.h"

//TODO divide them in other file as usage after 3d support


namespace VEGA {
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<Scene>& context) {
        m_Context = context;
		m_SelectionContext = {};
    }

    void SceneHierarchyPanel::OnImGuiRender() {
        ImGui::Begin("scene hierarchy");

        auto view = m_Context->m_registry.view<TagComponent>();
        for (auto entityHandle : view) {
            Entity entity{ entityHandle, m_Context.get() };
            DrawEntityNode(entity);
        }

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered())
			m_SelectionContext = {};

		if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_NoOpenOverItems))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}

		ImGui::End();




        ImGui::Begin("Properties");
        if (m_SelectionContext) {
            DrawComponents(m_SelectionContext);
        
        
        }
        ImGui::End();
    }

	void SceneHierarchyPanel::DrawEntityNode(Entity entity) {
		auto& tc = entity.GetComponent<TagComponent>();

		ImGui::PushID((uint32_t)entity);

		ImGuiTreeNodeFlags flags =
			((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
			ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanFullWidth;

		bool opened = ImGui::TreeNodeEx(tc.Tag.c_str(), flags);

		if (ImGui::IsItemClicked())
			m_SelectionContext = entity;

		bool entityDeleted = false;

		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			ImGui::OpenPopup("EntityPopup");

		if (ImGui::BeginPopup("EntityPopup"))
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
			ImGui::TreePop();

		ImGui::PopID();

		if (entityDeleted)
			m_Context->DestroyEntity(entity);
	}

    static void DrawVec3Control(const std::string& label,glm::vec3& value,f32 resetValue = 0.0f , f32 columeWidth = 100.0f)
    {
        ImGui::PushID(label.c_str());
        
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0,columeWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();
        
        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
        
        float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight * 1.0f , lineHeight };
        
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.8f, 0.1f, 0.1f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.7f, 0.05f, 0.05f, 1.0f));
        
        if (ImGui::Button("X", buttonSize))
            value.x = resetValue;
        ImGui::PopStyleColor(3);
      
        
        ImGui::SameLine();
        ImGui::DragFloat("##x",&value.x,0.01f,0.0f,0.0f,"%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();
        
          
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.6f, 0.1f, 1.0f));
        if (ImGui::Button("Y", buttonSize))
            value.y = resetValue;
        ImGui::PopStyleColor(3);
        
		ImGui::SameLine();
		ImGui::DragFloat("##y", &value.y, 0.01f,0.0f,0.0f,"%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
        
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.2f, 0.3f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.4f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.1f, 0.2f, 0.7f, 1.0f));
        
        
        if (ImGui::Button("Z", buttonSize))
            value.z = resetValue;
        ImGui::PopStyleColor(3);
        
        ImGui::SameLine();
		ImGui::DragFloat("##z", &value.z, 0.01f,0.0f,0.0f,"%.2f");
		ImGui::PopItemWidth();

        ImGui::PopStyleVar();
        
        ImGui::Columns(1);
        ImGui::PopID();
    }


	const ImGuiTreeNodeFlags TreeNodeFlag = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowOverlap | ImGuiTreeNodeFlags_FramePadding;

	template<typename T, typename UIFunction>
	static void DrawComponents(const std::string& name, Entity entity, UIFunction function)
	{
		if (entity.HasComponent<T>())
		{
			auto& components = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;

			
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3.0f);
			ImGui::Separator();

			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), TreeNodeFlag, name.c_str());
			ImGui::PopStyleVar();

			
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);

			ImGui::PushID(name.c_str());
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;
				ImGui::EndPopup();
			}
			ImGui::PopID(); 

			if (open)
			{
				function(components);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	}


    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strncpy_s(buffer, tag.c_str(), sizeof(buffer));

			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}
		ImGui::SameLine();
		ImGui::PushItemWidth(-1);


		if (ImGui::Button("Add Components"))
			ImGui::OpenPopup("AddComponents");

		if (ImGui::BeginPopup("AddComponents"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_SelectionContext.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_SelectionContext.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();
        
        ::VEGA::DrawComponents<TransformComponent>("Transfrom ", entity,
            [](auto& components)
            {
				
				DrawVec3Control("Traslation", components.Translation);
				glm::vec3 rotation = glm::degrees(components.Rotation);
				DrawVec3Control("Rotation", rotation);
                components.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", components.Scale, 1.0f);
            });
		::VEGA::DrawComponents<CameraComponent>("Camera Renderer", entity,
			[](auto& components)
			{
				
				auto& camera = components.Camera;

				ImGui::Checkbox("Primary", &components.Primary);

				const char* projectionTypeString[] = { "Projection","Orthographic" };
				const char* currnetProjectionTypeString = projectionTypeString[(int)camera.GetProjectionType()];
				if (ImGui::BeginCombo("Projection", currnetProjectionTypeString))
				{
					for (int i{ 0 }; i < 2; i++) {
						bool isSelected = currnetProjectionTypeString == projectionTypeString[i];

						if (ImGui::Selectable(projectionTypeString[i], isSelected))
						{
							currnetProjectionTypeString = projectionTypeString[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}
						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perpective)
				{

					f32 ProjFOV = glm::degrees(camera.GetProjectionFOV());
					
					if (ImGui::DragFloat("FOV", &ProjFOV))
					{
						camera.SetPerspectiveFOV(glm::radians(ProjFOV));
					}
					f32 ProjNear = camera.GetProjectionNear();
					if (ImGui::DragFloat("FOV Near", &ProjNear))
					{
						camera.SetPerpecstiveNear(ProjNear);
					}
					f32 ProjFar = camera.GetProjectionFar();
					if (ImGui::DragFloat("FOV Far", &ProjFar))
					{
						camera.SetPerspecstiveFar(ProjFar);
					}
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orhtographic)
				{
					f32 orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
					{
						camera.SetOrthographicSize(orthoSize);
					}
					f32 orthoNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
					{
						camera.SetOrthoGraphicNearClip(orthoNear);
					}
					f32 orthoFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
					{
						camera.SetOrthoGraphicFarClip(orthoFar);
					}

					ImGui::Checkbox("Fixed aspect ratio", &components.FixedAspectRatio);
				}

			});


		::VEGA::DrawComponents<SpriteRendererComponent>("Sprite Renderer", entity,
			[](SpriteRendererComponent& src)
			{
				ImGui::ColorEdit4("Color", glm::value_ptr(src.Color));
			});
    }
	
} // namespace VEGA
