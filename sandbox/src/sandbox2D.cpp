#include "Sandbox2d.h"



#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"
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

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(VEGA::Timestep ts)
{
    m_CameraController.OnUpdate(ts);

    VEGA::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    VEGA::RenderCommand::Clear();
   

    VEGA::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<VEGA::OpenGLShader>(textureShader)->Bind();
    std::dynamic_pointer_cast<VEGA::OpenGLShader>(textureShader)->SetUniformFloat4 ("u_color", blueColor);


    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Transform);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    textureShader->Bind();
	
	VEGA::Renderer::Submit(textureShader, m_SqaureVA, transform);
  


    VEGA::Renderer::EndScene();
}

void Sandbox2D::OnEvent(VEGA::Event& event)
{

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::Text("Square Position: (%.2f, %.2f, %.2f)", m_Transform.x, m_Transform.y, m_Transform.z);
	ImGui::ColorEdit3("Square Color", glm::value_ptr(blueColor));
	ImGui::End();
}
