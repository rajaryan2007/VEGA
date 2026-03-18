#include "SceneHierachyPanel.h"
#include "VEGA/Scene/Components.h"
#include "glm/trigonometric.hpp"
#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "imgui/imgui_internal.h"

namespace VEGA {
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<Scene>& context) {
        m_Context = context;
    }

    void SceneHierarchyPanel::OnImGuiRender() {
        ImGui::Begin("scene hierarchy");

        auto view = m_Context->m_registry.view<TagComponent>();
        for (auto entityHandle : view) {
            Entity entity{ entityHandle, m_Context.get() };
            DrawEntityNode(entity);
        }

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_SelectionContext = {};
        ImGui::End();

        ImGui::Begin("Properties");
        if (m_SelectionContext) {
            DrawComponents(m_SelectionContext);
        }
        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity) {
        auto& tc = entity.template GetComponent<TagComponent>();

        ImGuiTreeNodeFlags flags =
            ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
            ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened =
            ImGui::TreeNodeEx((void*)(u64)(u32)entity, flags, tc.Tag.c_str());

        if (ImGui::IsItemClicked()) {
            m_SelectionContext = entity;
        }

        if (opened) {
            ImGui::TreePop();
        }
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

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
        if (entity.HasComponent<TagComponent>())
        {
            auto& tag = entity.GetComponent<TagComponent>().Tag;

            static char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& tc = entity.GetComponent<TransformComponent>();
                DrawVec3Control("Traslation",tc.Translation);
                glm::vec3 rotation = glm::degrees(tc.Rotation);
                DrawVec3Control("Rotation",rotation);
                tc.Rotation = glm::radians(rotation);
                DrawVec3Control("Scale",tc.Scale,1.0f);
                
                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<CameraComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")){
                auto& cameraComponent = entity.GetComponent<CameraComponent>();
                auto& camera = cameraComponent.Camera;

                ImGui::Checkbox("Primary", &cameraComponent.Primary);

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
                    //f32 ProjFOV = camera.GetProjectionFOV();
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

                    ImGui::Checkbox("Fixed aspect ratio", &cameraComponent.FixedAspectRatio);
                }

                ImGui::TreePop();

        }
    }
        if (entity.HasComponent<SpriteRendererComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
            {
                auto& src = entity.GetComponent<SpriteRendererComponent>();
                ImGui::ColorEdit4("Color",glm::value_ptr(src.Color));
                ImGui::TreePop();
            }
        }
  }
} // namespace VEGA
