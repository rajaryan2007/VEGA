#include "uhepch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace UHE {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
