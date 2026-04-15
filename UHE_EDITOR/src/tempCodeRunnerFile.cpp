void Editor::UI_Toolbar()
  {
      float padding = 8.0f;
      float buttonSize = 24.0f;
      float windowHeight = buttonSize + padding * 2.0f;
      float windowWidth = buttonSize + padding * 2.0f;

      ImGui::SetNextWindowPos(ImVec2(
          m_ViewportPos.x + (m_ViewportSize.x * 0.5f) - (windowWidth * 0.5f),
          m_ViewportPos.y + 10.0f
      ));

      ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));

      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding, padding));
      
      ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.12f, 0.12f, 0.12f, 0.8f));
      
      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
      auto& colors = ImGui::GetStyle().Colors;
      const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
      const auto& buttonActive = colors[ImGuiCol_ButtonActive];
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

      ImGui::Begin("##toolbar", nullptr,
          ImGuiWindowFlags_NoDecoration |
          ImGuiWindowFlags_NoMove |
          ImGuiWindowFlags_NoDocking |
          ImGuiWindowFlags_NoSavedSettings);

      Ref<Texture2D> icon = m_SceneState == SceneState::Edit ? m_IconPlay : m_IconStop;

      if (ImGui::ImageButton(
          "##Play",
          (ImTextureID)(uintptr_t)icon->GetRendererID(),
          ImVec2(buttonSize, buttonSize)
      ))
      {
          if (m_SceneState == SceneState::Edit)
              OnScreenPlay();
          else
              OnSceneStop();
      }

      ImGui::End();

      ImGui::PopStyleColor(4);
      ImGui::PopStyleVar(3);
  }