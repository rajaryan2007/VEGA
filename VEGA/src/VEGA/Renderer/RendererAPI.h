#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "VEGA/Renderer/VertexArray.h"
namespace VEGA {
	class RendererAPI 
	{
	public:
		enum class API { None = 0, OpenGL = 1 /*, ... */ };
	public:
		virtual void Init() = 0;
		virtual void SetViewport(u32 x, u32 y, u32 width, u32 height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray,u32 indexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
   

	};
}