#include "Sandbox2D.h"

#define STATISTICS
#include <chrono>

//#include "Platform/OpenGL/OpenGLShader.h"
//#include "Platform/OpenGL/OpenGLTexture.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>






Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_Transform(0.0f, 0.0f, 0.0f)
{

}

void Sandbox2D::OnAttach()
{
    
	
     

    m_SqaureVA = (VEGA::VertexArray::Create());

    float vertiecsSquare[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

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
    
    m_Test = VEGA::SubTexture2D::CreateFromCoords(m_TestTexture, { 1080,1920 }, {1280,1280});

	// Init here
	m_ParticleProps.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_ParticleProps.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_ParticleProps.SizeBegin = 0.5f, m_ParticleProps.SizeVariation = 0.3f, m_ParticleProps.SizeEnd = 0.0f;
	m_ParticleProps.LifeTime = 10.0f;
	m_ParticleProps.Velocity = { 0.0f, 0.0f };
	m_ParticleProps.VelocityVariation = { 3.0f, 1.0f };
	m_ParticleProps.Position = { 0.0f, 0.0f };

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(VEGA::Timestep ts)
{
    
        VG_PROFILE_FUNCTION();

        {
           // PROFILE_SCOPE("Camera contorller")
                m_CameraController.OnUpdate(ts);
        }
        VEGA::Renderer2D::ResetStats();
        {
           // PROFILE_SCOPE("reder prep")
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
                 VEGA::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), {5.0f, 5.0f}, blueColor);


                //VEGA::Renderer2D::DrawRotatedQuad({ 2.0f,0.20f }, { 1.0f, 1.0f }, rotation, redColor);
                //VEGA::Renderer2D::DrawRotatedQuad({ 0.0f,0.0f }, { 1.0f, 1.0f }, rotation, m_TextureLOGO);
                //VEGA::Renderer2D::DrawQuad({ 0.5f,-0.5f,0.0f }, { 0.5f, 1.0f }, redColor);
                VEGA::Renderer2D::DrawQuad({ 0.0f,0.0f }, { 1.0f, 1.0f }, m_Test);
                
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
        //VEGA::Renderer::EndScene();
        {
           // PROFILE_SCOPE("particle");
            if (VEGA::Input::IsMouseButtonPressed(VG_MOUSE_BUTTON_LEFT))
            {
                auto [x, y] = VEGA::Input::GetMousePosition();
                auto width = VEGA::Application::Get().GetWindow().GetWidth();
                auto height = VEGA::Application::Get().GetWindow().GetHeight();

                auto bounds = m_CameraController.GetBounds();
                auto pos = m_CameraController.GetCamera().GetPosition();
                x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
                y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
                m_ParticleProps.Position = { x + pos.x, y + pos.y };
                for (int i = 0; i < 5; i++)
                    m_ParticleSystem.Emit(m_ParticleProps);
            }

            m_ParticleSystem.OnUpdate(ts);
            m_ParticleSystem.OnRender(m_CameraController.GetCamera());
        }
}

void Sandbox2D::OnEvent(VEGA::Event& event)
{
    m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{ 
    VG_PROFILE_FUNCTION();



	ImGui::Begin("Settings");
	
	auto stats = VEGA::Renderer2D::GetStats();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Index: %d", stats.GetTotalIndexCount());




    ImGui::Text("Square Position: (%.2f, %.2f, %.2f)", m_Transform.x, m_Transform.y, m_Transform.z);
	ImGui::ColorEdit3("Square Color", glm::value_ptr(blueColor));
	ImGui::End();
}
