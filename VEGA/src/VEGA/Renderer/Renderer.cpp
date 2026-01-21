#include "vgpch.h"
#include "Renderer.h"
#include "RendererAPI.h"

namespace VEGA {

    void Renderer::BeginScene() {
        // Implementation for beginning a scene
	}

    void Renderer::EndScene() {
        // Implementation for ending a scene
	}

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
        // Implementation for submitting a vertex array to be rendered
		RenderCommand::DrawIndexed(vertexArray);
	}

}