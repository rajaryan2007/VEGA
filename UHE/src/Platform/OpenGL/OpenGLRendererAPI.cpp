#include "OpenGLRendererAPI.h"
#include "uhepch.h"


#include <glad/glad.h>

namespace UHE {
void OpenGLRendererAPI::Init() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
}

void OpenGLRendererAPI::SetViewport(u32 x, u32 y, u32 width, u32 height) {
  glViewport(x, y, width, height);
}

void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.r, color.g, color.b, color.a);
}

void OpenGLRendererAPI::Clear() {
  VG_GPU_ZONE("OpenGLRendererAPI::Clear");
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::DrawIndexed(
    const std::shared_ptr<VertexArray> &vertexArray, u32 indexCount) {
  VG_GPU_ZONE("OpenGLRendererAPI::DrawIndexed");
  if (indexCount == 0)
    return;

  vertexArray->Bind();
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
  // glBindTexture(GL_TEXTURE_2D, 0);
}
} // namespace UHE
