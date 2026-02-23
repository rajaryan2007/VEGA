#include "Sandbox2d.h"


#include <chrono>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VEGA/Renderer/Renderer2D.h"





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
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(VEGA::Timestep ts)
{
    
        VG_PROFILE_FUNCTION();

        {
            PROFILE_SCOPE("Camera contorller")
                m_CameraController.OnUpdate(ts);
        }
        {
            PROFILE_SCOPE("reder prep")
                VEGA::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            VEGA::RenderCommand::Clear();
        }


        {
            PROFILE_SCOPE("Renderer2D::Scene");
            VEGA::Renderer2D::BeginScene(m_CameraController.GetCamera());
            {

                PROFILE_SCOPE("DrawQuad");
                //VEGA::Renderer2D::DrawQuad(m_Transform, { 5.0f, 5.0f }, blueColor);


                VEGA::Renderer2D::DrawRotatedQuad({ 0.0f,0.0f }, { 1.0f, 1.0f },glm::radians(00.0f), blueColor);
                //VEGA::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { 0.5f, 1.0f }, blueColor);
                //VEGA::Renderer2D::DrawRotatedQuad(glm::vec3(0.0f, 0.0f, 0.1f), { 1.0f, 1.0f },glm::radians(45.0f), m_TextureLOGO);
            }
        }
        VEGA::Renderer2D::EndScene();
        //VEGA::Renderer::EndScene();
    
}

void Sandbox2D::OnEvent(VEGA::Event& event)
{
    m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{ 
    VG_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::Text("Square Position: (%.2f, %.2f, %.2f)", m_Transform.x, m_Transform.y, m_Transform.z);
	ImGui::ColorEdit3("Square Color", glm::value_ptr(blueColor));
	ImGui::End();
}
