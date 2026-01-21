#include "vgpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace VEGA {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
