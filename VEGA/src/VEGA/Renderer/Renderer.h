#pragma once

#include "RendererAPI.h"
#include "VEGA/Renderer/VertexArray.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include <memory>


namespace VEGA
{   
	class Shader;
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}

	private:
		/*static RendererAPI::API s_RendererAPI;*/

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* s_SceneData;
	};
}

