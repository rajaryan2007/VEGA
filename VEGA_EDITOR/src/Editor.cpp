#include "editor.h"



#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const u32 s_mapWidth = 25;

static const char* s_MapTIles =
"GGGGGGGGGGGGGGGGGGGGGGGGG"
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
"GGGGGGGGGGGGGGGGGGGGGGGGG"
;

namespace VEGA
{



    Editor::Editor()
        : Layer("Editor"), m_CameraController(1280.0f / 720.0f), m_Transform(0.0f, 0.0f, 0.0f)
    {

    }

    void Editor::OnAttach()
    {




        m_SqaureVA = (VEGA::VertexArray::Create());

        float vertiecsSquare[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };


        VEGA::FrameBufferSpecification fbspec;
        fbspec.Width = 1280;
        fbspec.Height = 720;
        m_FrameBuffer = VEGA::FrameBuffer::Create(fbspec);

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



        textureShader = VEGA::Shader::Create("assests/shaders/flatSquare.glsl");
        m_TextureLOGO = VEGA::Texture2D::Create("assests/textures/Lily.jpg");
        m_TestTexture = VEGA::Texture2D::Create("assests/textures/bmw.jpg");
        m_TestSprite = VEGA::Texture2D::Create("assests/textures/water.png");

        m_mapWidth = s_mapWidth;
        m_mapHeight = strlen(s_MapTIles) / s_mapWidth;

        m_Test = VEGA::SubTexture2D::CreateFromCoords(m_TextureLOGO, { 1080,1920 }, { 1280,1280 });
        Land['W'] = VEGA::SubTexture2D::CreateFromPixels(
            m_TestSprite,
            { 900, 51 },   // flipped Y
            { 87, 99 }
        );
        Land['G'] = VEGA::SubTexture2D::CreateFromPixels(
            m_TestSprite,
            { 98, 479 },     // pixel position
            { 164, 127 }     // pixel size
        );
        dirt = VEGA::SubTexture2D::CreateFromCoords(m_TestSprite, { 2,3 }, { 32,32 });

        // Init here


    }

    void Editor::OnDetach()
    {

    }

    void Editor::OnUpdate(VEGA::Timestep ts)
    {

        VG_PROFILE_FUNCTION();

        {
            // PROFILE_SCOPE("Camera contorller")
            m_CameraController.OnUpdate(ts);
        }
        VEGA::Renderer2D::ResetStats();
        {
            // PROFILE_SCOPE("reder prep")
            m_FrameBuffer->Bind();
            VEGA::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            VEGA::RenderCommand::Clear();
        }


        {
            // PROFILE_SCOPE("Renderer2D::Scene");
            VEGA::Renderer2D::BeginScene(m_CameraController.GetCamera());
            {
                static float rotation = 0.0f;
                rotation += 1.0f * ts;

                //PROFILE_SCOPE("DrawQuad");
                 //VEGA::Renderer2D::DrawQuad(glm::vec3(-0.5f, -00.5f, 0.0f), { 1.0f, 1.0f }, m_TextureLOGO);
                VEGA::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), { 5.0f, 5.0f }, blueColor);


                //VEGA::Renderer2D::DrawRotatedQuad({ 2.0f,0.20f }, { 1.0f, 1.0f }, rotation, redColor);
                //VEGA::Renderer2D::DrawRotatedQuad({ 0.0f,0.0f }, { 1.0f, 1.0f }, rotation, m_TextureLOGO);
                //VEGA::Renderer2D::DrawQuad({ 0.5f,-0.5f,0.0f }, { 0.5f, 1.0f }, redColor);
               // VEGA::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f, 1.0f }, m_TestSubSprite);
               // VEGA::Renderer2D::DrawQuad({ 0.5f,0.0f }, { 1.0f, 1.0f }, grass);
               // VEGA::Renderer2D::DrawQuad({ 0.0f,0.5f }, { 1.0f, 1.0f }, water);
                //VEGA::Renderer2D::DrawQuad({ 0.5f,0.5f }, { 1.0f, 1.0f }, dirt);


                for (u32 y = 0; y < m_mapHeight; y++) {
                    for (u32 x = 0; x < m_mapWidth; x++) {

                        char tileType = s_MapTIles[x + y * m_mapWidth];
                        VEGA::Ref<VEGA::SubTexture2D> texture;

                        if (Land.find(tileType) != Land.end())
                        {
                            texture = Land[tileType];
                        }
                        else
                        {
                            texture = dirt;
                        }
                        VEGA::Renderer2D::DrawQuad({ x - m_mapWidth / 2.0f,y - m_mapHeight / 2.0f }, { 1.0f, 1.0f }, texture);

                    }
                }





                for (f32 y = -5.0f; y < 5.0f; y += 0.5f)
                {
                    for (f32 x = -5.0f; x < 5.0f; x += 0.5f)
                    {
                        glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f };
                        VEGA::Renderer2D::DrawQuad({ x,y,-0.2f }, { 0.45f, 0.45f }, color);
                    }
                }


            }
        }

        VEGA::Renderer2D::EndScene();
        m_FrameBuffer->UnBind();
        //VEGA::Renderer::EndScene();

    }

    void Editor::OnEvent(VEGA::Event& event)
    {
        m_CameraController.OnEvent(event);
    }

    void Editor::OnImGuiRender()
    {
        VG_PROFILE_FUNCTION();

        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();

            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);

            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("file")) {
                if (ImGui::MenuItem("exit")) VEGA::Application::Get().Close();
                ImGui::EndMenu();

            }
        }
        ImGui::EndMenuBar();

        ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::End();


        // ----- YOUR SETTINGS WINDOW -----

        ImGui::Begin("Settings");

        auto stats = VEGA::Renderer2D::GetStats();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
            1000.0f / ImGui::GetIO().Framerate,
            ImGui::GetIO().Framerate);

        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Index: %d", stats.GetTotalIndexCount());

        ImGui::Text("Square Position: (%.2f, %.2f, %.2f)",
            m_Transform.x, m_Transform.y, m_Transform.z);

        ImGui::ColorEdit3("Square Color", glm::value_ptr(blueColor));
       

        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
        ImGui::Begin("Viewport");
        ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
        if ( m_ViewPortSize != *((glm::vec2*)&viewPortSize) && viewPortSize.x > 0.0f && viewPortSize.y > 0.0f)
        {
            
            m_FrameBuffer->Resize((u32)viewPortSize.x, (u32)viewPortSize.y);
            m_ViewPortSize = { viewPortSize.x,viewPortSize.y };
       
            m_CameraController.OnResize(viewPortSize.x, viewPortSize.y);
        }
        m_ViewPortSize = { viewPortSize.x,viewPortSize.y };
    	u32 textureId = m_FrameBuffer->GetColorAttacmentRendererID();
        
        ImGui::Image((void*)textureId, ImVec2{ m_ViewPortSize.x,m_ViewPortSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
        
        ImGui::End();
        ImGui::PopStyleVar();
    }
}