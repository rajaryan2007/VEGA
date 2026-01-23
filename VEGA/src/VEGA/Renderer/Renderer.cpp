#include "vgpch.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Shader.h"
namespace VEGA {

	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera) {
        // Implementation for beginning a scene
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

    void Renderer::EndScene() 
	{
        // Implementation for ending a scene
	}

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader) {
        // Implementation for submitting a vertex array to be rendered
		
		shader->Bind();
		shader->SetUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	

}