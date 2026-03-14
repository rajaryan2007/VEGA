#include "SceneHierachyPanel.h"
#include "VEGA/Scene/Components.h"
#include <ImGui/imgui.h>

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

} // namespace VEGA
