#include "SceneHierachyPanel.h"
#include "VEGA/Scene/Components.h"
#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>


namespace VEGA {
SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &context) {
  SetContext(context);
}

void SceneHierarchyPanel::SetContext(const Ref<Scene> &context) {
  m_Context = context;
}

void SceneHierarchyPanel::OnImGuiRender() {
  ImGui::Begin("scene hierarchy");

  auto view = m_Context->m_registry.view<TagComponent>();
  for (auto entityHandle : view) {
    Entity entity{entityHandle, m_Context.get()};
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
  auto &tc = entity.template GetComponent<TagComponent>();

  ImGuiTreeNodeFlags flags =
      ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) |
      ImGuiTreeNodeFlags_OpenOnArrow;
  bool opened =
      ImGui::TreeNodeEx((void *)(u64)(u32)entity, flags, tc.Tag.c_str());

  if (ImGui::IsItemClicked()) {
    m_SelectionContext = entity;
  }
      
      if (opened) {
       ImGui::TreePop();
     }
}

void SceneHierarchyPanel::DrawComponents(Entity entity)
{
    if (entity.HasComponent<TagComponent>())
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;
        
        static char buffer[256];
        memset(buffer, 0, sizeof(buffer));
        strcpy_s(buffer, sizeof(buffer), tag.c_str());
        if (ImGui::InputText("Tag",buffer,sizeof(buffer))) 
        {
            tag = std::string(buffer);
        }
    }

    if (entity.HasComponent<TransformComponent>())
    {   
        if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
        {
            auto& transform = entity.GetComponent<TransformComponent>().Transform;
            (ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.05f));

            ImGui::TreePop();
        }
    }
}

} // namespace VEGA
