#include "editor.h"

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ImGuizmo.h"
#include "VEGA/Math/Math.h"

static const u32 s_mapWidth = 25;

static const char *s_MapTIles = "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGWWWGGGGGGGGGGGG"
                                "GGGGGGGWWWWWWWGGGGGGGGGGG"
                                "GGGGGGWWWWWWWWWGGGGGGGGGG"
                                "GGGGGGWWWWWWWWWGGGGGGGGGG"
                                "GGGGGGWWWWWWWWWGGGGGGGGGG"
                                "GGGGGGGWWWWWWWGGGGGGGGGGG"
                                "GGGGGGGGWWWGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG"
                                "GGGGGGGGGGGGGGGGGGGGGGGGG";

namespace VEGA {

Editor::Editor()
    : Layer("Editor"), m_CameraController(1280.0f / 720.0f),
      m_Transform(0.0f, 0.0f, 0.0f), m_SceneHireacyPanel(m_ActiveScene) {}

void Editor::OnAttach() {
  
  m_SqaureVA = (VEGA::VertexArray::Create());

  float vertiecsSquare[] = {
      -0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f,
      0.5f,  0.5f,  0.0f, -0.5f, 0.5f,  0.0f,
  };

  VEGA::FrameBufferSpecification fbspec;
  fbspec.Attachments = {VEGA::FrameBufferTextureFromat::RGBA8,
						VEGA::FrameBufferTextureFromat::RED_INTEGER,
                        VEGA::FrameBufferTextureFromat::Depth
                        
  };
  fbspec.Width = 1280; 
  fbspec.Height = 720;
  m_FrameBuffer = VEGA::FrameBuffer::Create(fbspec);

  m_ActiveScene = CreateRef<Scene>();

  // auto square = m_ActiveScene->CreateEntity();
#if 0
        std::shared_ptr<VEGA::VertexBuffer> squareVB;
        squareVB.reset(VEGA::VertexBuffer::Create(vertiecsSquare, sizeof(vertiecsSquare)));

        VEGA::BufferLayout SVlayout = {
            {VEGA::ShaderDataType::Float3,"a_Position"},


        };

        squareVB->SetLayout(SVlayout);

        m_SqaureVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[] = {
            0, 1, 2,
            2, 3, 0
        };
        std::shared_ptr<VEGA::IndexBuffer> squareIB;
        squareIB.reset(VEGA::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SqaureVA->SetIndexBuffer(squareIB);



        textureShader = Shader::Create("assests/shaders/flatSquare.glsl");
        m_TextureLOGO = Texture2D::Create("assests/textures/Lily.jpg");
        m_TestTexture = Texture2D::Create("assests/textures/bmw.jpg");
        m_TestSprite = Texture2D::Create("assests/textures/water.png");

        m_mapWidth = s_mapWidth;
        m_mapHeight = strlen(s_MapTIles) / s_mapWidth;

        m_Test = SubTexture2D::CreateFromCoords(m_TextureLOGO, { 1080,1920 }, { 1280,1280 });
        Land['W'] = SubTexture2D::CreateFromPixels(
            m_TestSprite,
            { 900, 51 },   // flipped Y
            { 87, 99 }
        );
        Land['G'] = SubTexture2D::CreateFromPixels(
            m_TestSprite,
            { 98, 479 },     // pixel position
            { 164, 127 }     // pixel size
        );
        dirt = SubTexture2D::CreateFromCoords(m_TestSprite, { 2,3 }, { 32,32 });

        // Init here
        auto square = m_ActiveScene->CreateEntity("square");
        square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f,1.0f,1.0f,1.0f });

        auto redSqaure = m_ActiveScene->CreateEntity("redSquare");
        redSqaure.AddComponent<SpriteRendererComponent>(glm::vec4{0.1f,1.0f,0.5f,1.0f});

        m_Square = square;

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Camerasecond");
		auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
		cc.Primary = false;
        class CameraController : public ScriptableEntity
        {
        public:
            void OnCreate()
            {
               
            }
            void OnDestroy()
            {

            }
            void OnUpdate(Timestep ts)
            {
                auto& transform = GetComponent<TransformComponent>().Translation;
                f32 speed = 5.0f;
                

                if (Input::IsKeyPressed(Key::A))
                    transform.x -= speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    transform.x += speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    transform.y -= speed * ts;
				if (Input::IsKeyPressed(Key::S))
					transform.y += speed * ts;

            }
        };

        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

#endif
  // m_SceneHireacyPanel(m_ActiveScene);
  m_EditorCamera = EditorCamera(45.0f, 1.766f, 0.1f, 1000.0f);
  m_SceneHireacyPanel.SetContext(m_ActiveScene);
}

void Editor::OnDetach() {}

void Editor::OnUpdate(VEGA::Timestep ts) {

  VG_PROFILE_FUNCTION();

  // PROFILE_SCOPE("Camera contorller")
  m_CameraController.OnUpdate(ts);

  VEGA::Renderer2D::ResetStats();
  {
    // PROFILE_SCOPE("reder prep")
    m_FrameBuffer->Bind();
    VEGA::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    VEGA::RenderCommand::Clear();
  }
  // PROFILE_SCOPE("Renderer2D::Scene");

  static float rotation = 0.0f;
  rotation += 1.0f * ts;

  // PROFILE_SCOPE("DrawQuad");
  // VEGA::Renderer2D::DrawQuad(glm::vec3(-0.5f, -00.5f, 0.0f), { 1.0f, 1.0f },
  // m_TextureLOGO);

  // VEGA::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), { 5.0f, 5.0f },
  // blueColor);
  if (m_ViewPortFocused) {
    m_CameraController.OnUpdate(ts);
    m_EditorCamera.OnUpdate(ts);
  }
  
  m_FrameBuffer->ClearAttachment(1,-1);

  m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);

  auto [mx, my] = ImGui::GetMousePos();
  mx -= m_ViewPortBounds[0].x;
  my -= m_ViewPortBounds[1].y;
  glm::vec2 viewportSize = m_ViewPortBounds[1] - m_ViewPortBounds[0];

  my = viewportSize.y - my;

  i32 mouseX = (i32)mx;
  i32 mouseY= (i32)my;

  if(mouseX >= 0 && mouseY >= 0 && mouseX < (i32)viewportSize.x && mouseY < (i32)viewportSize.y)
  {
	  int PixelData = m_FrameBuffer->ReadPixel(1, mouseX, mouseY);
	  VG_CORE_WARN("Pixel data at ({0}, {1}): {2}", mouseX, mouseY, PixelData);
  }

  VG_CORE_ASSERT(mouseX >= 0 && mouseY >= 0 && mouseX < (i32)viewportSize.x mouseY < (i32)viewportSize.y,
	  "Mouse position is out of bounds!");

  m_FrameBuffer->UnBind();
  // VEGA::Renderer::EndScene();
}

void Editor::OnEvent(VEGA::Event &event) {
  m_CameraController.OnEvent(event);
  m_EditorCamera.OnEvent(event);

  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<KeyPressedEvent>(
      [this](KeyPressedEvent &e) { return onKeyPressed(e); });
}

bool Editor::onKeyPressed(KeyPressedEvent &e) {
  if (e.GetRepeatCount() > 0)
    return false;

  bool controlPressed = (Input::IsKeyPressed(Key::LeftControl) ||
                         Input::IsKeyPressed(Key::RightControl));
  bool shift = (Input::IsKeyPressed(Key::LeftShift) ||
                Input::IsKeyPressed(Key::RightShift));
  switch (e.GetKeyCode()) {
  case Key::N: {
    if (controlPressed) {
      NewScene();
    }
    break;
  }
  case Key::O: {
    if (controlPressed)
      OpenScene();

    break;
  }
  case Key::S: {
    if (controlPressed)
      SaveSceneAs();

    break;
  }
    // gizmo

  case Key::Q:
    m_GizmoType = 1;
    break;
  case Key::W:
    m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
    break;
  case Key::E:
    m_GizmoType = ImGuizmo::OPERATION::ROTATE;
    break;
  case Key::R:
    m_GizmoType = ImGuizmo::OPERATION::SCALE;
    break;
  }
}

void Editor::NewScene() {
  m_ActiveScene = CreateRef<Scene>();
  m_ActiveScene->OnViewportResize((u32)m_ViewPortSize.x, (u32)m_ViewPortSize.y);
  m_SceneHireacyPanel.SetContext(m_ActiveScene);
}

void Editor::OpenScene() {
  std::string filepath = FileDialogs::OpenFile("VEGA Scene (*.vega)\0*.vega\0");
  if (!filepath.empty()) {
    m_ActiveScene = CreateRef<Scene>();
    m_ActiveScene->OnViewportResize((u32)m_ViewPortSize.x,
                                    (u32)m_ViewPortSize.y);
    m_SceneHireacyPanel.SetContext(m_ActiveScene);

    SceneSerializer serializer(m_ActiveScene);
    serializer.Deserialize(filepath);
  }
}

void DrawConsolePanel() {
  ImGui::Begin("Console");

  auto sink = VEGA::Log::GetImGuiSink();
  const auto &logs = sink->GetLogs();

  for (const auto &log : logs) {
    ImVec4 color;

    switch (log.Level) {
    case spdlog::level::warn:
      color = ImVec4(1, 1, 0, 1);
      break;
    case spdlog::level::err:
      color = ImVec4(1, 0, 0, 1);
      break;
    case spdlog::level::critical:
      color = ImVec4(1, 0, 1, 1);
      break;
    default:
      color = ImVec4(1, 1, 1, 1);
      break;
    }

    ImGui::TextColored(color, "%s", log.Message.c_str());
  }

  if (ImGui::Button("Clear"))
    sink->Clear();

  // auto-scroll
  if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    ImGui::SetScrollHereY(1.0f);

  ImGui::End();
}

void Editor::SaveSceneAs() {
  std::string filepath = FileDialogs::SaveFile("VEGA Scene (*.vega)\0.vega\0");

  if (!filepath.empty()) {
    SceneSerializer serializer(m_ActiveScene);
    serializer.Serialize(filepath);
  }
}

void Editor::OnImGuiRender() {
  VG_PROFILE_FUNCTION();

  static bool dockspaceOpen = true;
  static bool opt_fullscreen = true;
  static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

  ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

  if (opt_fullscreen) {
    const ImGuiViewport *viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |=
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  }

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

  ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {

      if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
        NewScene();
      }

      if (ImGui::MenuItem("Open...", "Ctrl+O")) {
        OpenScene();
      }

      if (ImGui::MenuItem("Save As...", "Ctrl+S")) {
        SaveSceneAs();
      }

      if (ImGui::MenuItem("Exit"))
        VEGA::Application::Get().Close();
      ImGui::EndMenu();
    }
  }
  ImGui::EndMenuBar();

  ImGui::PopStyleVar(2);

  ImGuiIO &io = ImGui::GetIO();
  ImGuiStyle &style = ImGui::GetStyle();
  f32 minWinSizeX = style.WindowMinSize.x;
  style.WindowMinSize.x = 370.0f;
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
  }

  style.WindowMinSize.x = minWinSizeX;

  ImGui::End();

  // your setting
  m_SceneHireacyPanel.OnImGuiRender();

  ImGui::Begin("Settings");

  auto stats = VEGA::Renderer2D::GetStats();
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Index: %d", stats.GetTotalIndexCount());

  ImGui::End();

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
  ImGui::Begin("Viewport");
  auto viewPortOffset = ImGui::GetCursorPos();



  m_ViewPortFocused = ImGui::IsWindowFocused();
  m_ViewPortHover = ImGui::IsWindowHovered();
  Application::Get().GetImguiLayer()->SetBlockEvent(!m_ViewPortFocused &&
                                                    !m_ViewPortHover);

  ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
  m_CameraController.OnResize(viewPortSize.x, viewPortSize.y);
  m_ActiveScene->OnViewportResize((u32)viewPortSize.x, (u32)viewPortSize.y);

  if (FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();viewPortSize.x > 0.0f && viewPortSize.y > 0.0f &&
      (spec.Width != viewPortSize.x || spec.Height != viewPortSize.y)) 
  {
    m_FrameBuffer->Resize((u32)viewPortSize.x, (u32)viewPortSize.y);
    m_EditorCamera.SetViewportSize((u32)viewPortSize.x, (u32)viewPortSize.y);
    m_ViewPortSize = {viewPortSize.x, viewPortSize.y};
  }

  m_ViewPortSize = {viewPortSize.x, viewPortSize.y};
  u32 textureId = m_FrameBuffer->GetColorAttacmentRendererID();

  ImGui::Image((void *)textureId, ImVec2{m_ViewPortSize.x, m_ViewPortSize.y},
               ImVec2{0, 1}, ImVec2{1, 0});

  auto WindowSize = ImGui::GetWindowPos();
  ImVec2 minBound = ImGui::GetWindowPos();
  minBound.x += viewPortOffset.x;
  minBound.y += viewPortOffset.y ;

  ImVec2 maxBound = { minBound.x + WindowSize.x, minBound.y + WindowSize.y };
  m_ViewPortBounds[0] = { minBound.x, minBound.y };
  m_ViewPortBounds[1] = { maxBound.x, maxBound.y }; 

  

  // Gizmos
  Entity SelectedEntity = m_SceneHireacyPanel.GetSelectedEntity();

  if (SelectedEntity) {

    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetDrawlist();
    f32 windowWidth = (f32)ImGui::GetWindowWidth();
    f32 windowheight = (f32)ImGui::GetWindowHeight();

    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y,
                      windowWidth, windowheight);

    if (m_GizmoType != -1) {
      glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();
      glm::mat4 cameraprojection = m_EditorCamera.GetProjection();

      auto &tc = SelectedEntity.GetComponent<TransformComponent>();
      glm::mat4 transform = tc.GetTransform();

      bool snap = Input::IsKeyPressed(Key::LeftControl);
      f32 snapValue = 0.5f;

      if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
        snapValue = 45.0f;

      f32 snapValues[3] = {snapValue, snapValue, snapValue};

      ImGuizmo::Manipulate(
          glm::value_ptr(cameraView), glm::value_ptr(cameraprojection),
          (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL,
          glm::value_ptr(transform), nullptr, snap ? snapValues : nullptr);

      if (ImGuizmo::IsUsing()) {
        glm::vec3 translation, rotation, scale;
        Math::DecomposeTransform(transform, translation, rotation, scale);
        glm::vec3 deltaRotation = rotation - tc.Rotation;
        tc.Translation = translation;
        tc.Rotation += deltaRotation;
        tc.Scale = scale;
      }
    }
  }

  ImGui::End();
  ImGui::PopStyleVar();

  DrawConsolePanel();
}

} // namespace VEGA