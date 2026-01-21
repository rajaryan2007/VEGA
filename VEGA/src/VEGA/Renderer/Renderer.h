#pragma once

#include "RendererAPI.h"
#include "VEGA/Renderer/VertexArray.h"
#include "RenderCommand.h"

namespace VEGA
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}

	private:
		static RendererAPI::API s_RendererAPI;
	};
}

