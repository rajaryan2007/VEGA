#pragma once

#include "OrthographicCamera.h"
#include "SubTexture2D.h"
#include "VEGA/Renderer/Texture.h"
#include "VEGA/Renderer/EditorCamera.h"

namespace VEGA {
class Camera;
class VEGA_API Renderer2D {
public:
  static void Init();
  static void Shutdown();
  static void BeginScene(const Camera &camera, const glm::mat4 &transform);
  static void BeginScene(const EditorCamera &camera);
  static void BeginScene(const OrthographicCamera& camera);
  static void flush();
  static void EndScene();

  // Primitives
  static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                       const glm::vec4 &color);
  static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                       const glm::vec4 &color);
  static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                       const Ref<Texture2D> &texture, f32 tiling_factor = 1.0f,
                       const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                       const Ref<Texture2D> &texture, f32 tiling_factor = 1.0f,
                       const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                       const Ref<SubTexture2D> &texture,
                       f32 tiling_factor = 1.0f,
                       const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                       const Ref<SubTexture2D> &texture,
                       f32 tiling_factor = 1.0f,
                       const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawQuad(const glm::mat4 &transform, const glm::vec4 &color);
  static void DrawQuad(const glm::mat4 &transform,
                       const Ref<Texture2D> &texture, f32 tiling_factor = 1.0f,
                       const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawQuad(const glm::mat4 &transform,
                       const Ref<Texture2D> &texture, const glm::vec2* texCoords,
                       f32 tiling_factor = 1.0f,
                       const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawQuad(const glm::mat4 &transform,
                       const Ref<SubTexture2D> &texture,
                       f32 tiling_factor = 1.0f,
                       const glm::vec4 &tintColor = glm::vec4(1.0f));

  static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size,
                              f32 rotation, const glm::vec4 &color);
  static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size,
                              f32 rotation, const glm::vec4 &color);
  static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size,
                              f32 rotation, Ref<Texture2D> &texture,
                              f32 tiling_factor = 1.0f,
                              const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size,
                              f32 rotation, Ref<Texture2D> &texture,
                              f32 tiling_factor = 1.0f,
                              const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size,
                              f32 rotation, Ref<SubTexture2D> &Subtexture,
                              f32 tiling_factor = 1.0f,
                              const glm::vec4 &tintColor = glm::vec4(1.0f));
  static void DrawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size,
                              f32 rotation, Ref<SubTexture2D> &Subtexture,
                              f32 tiling_factor = 1.0f,
                              const glm::vec4 &tintColor = glm::vec4(1.0f));

  struct Statistics {
    u32 DrawCalls = 0;
    u32 QuadCount = 0;

    u32 GetTotalVertexCount() { return QuadCount * 4; }
    u32 GetTotalIndexCount() { return QuadCount * 6; }
  };

  static Statistics GetStats();
  static void FlushAndReset();
  static void ResetStats();
};
} // namespace VEGA