#pragma once
#include "vgpch.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "VEGA/Animation/Animation2D/SpriteAnimation.h"
#include "VEGA/Core/Core.h"
#include "VEGA/Core/Timestep.h"
#include "VEGA/Renderer/Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


namespace VEGA {
struct VEGA_API TransformComponent {
  glm::vec3 Translation{0.0f};
  glm::vec3 Rotation{0.0f}; // assumed in degrees
  glm::vec3 Scale{1.0f};

  TransformComponent() = default;
  TransformComponent(const TransformComponent &) = default;

  TransformComponent(const glm::vec3 &translation) : Translation(translation) {}

  glm::mat4 GetTransform() const {
      glm::mat4 rotation = glm::mat4(glm::quat(Rotation));
        


    return glm::translate(glm::mat4(1.0f), Translation) * rotation *
           glm::scale(glm::mat4(1.0f), Scale);
  }
};
struct VEGA_API SpriteRendererComponent {
  glm::vec4 Color{1.0f};
  std::string TexturePath;
  Ref<Texture2D> Texture;
  f32 TilingFactor = 1.0f;

  bool UseSubTexture = false;
  glm::vec2 SubTextureCoords = {0.0f, 0.0f};
  glm::vec2 SubTextureCellSize = {16.0f, 16.0f};
  glm::vec2 SubTextureSpriteSize = {1.0f, 1.0f};

  SpriteRendererComponent() = default;
  SpriteRendererComponent(const SpriteRendererComponent &) = default;
  SpriteRendererComponent(const glm::vec4 &color) : Color(color) {}
};
struct VEGA_API TagComponent {
  std::string Tag;

  TagComponent() = default;
  TagComponent(const TagComponent &) = default;
  TagComponent(const std::string &tag) : Tag(tag) {}
};

struct VEGA_API CameraComponent {
  SceneCamera Camera;
  bool Primary = true;
  bool FixedAspectRatio = false;

  CameraComponent() = default;
  CameraComponent(const CameraComponent &) = default;
};

struct VEGA_API SpriteAnimationComponent {
  std::string SpriteSheetPath;
  SpriteAnimation Animation;
  glm::vec4 Color = {1.0f,1.0f,1.0f,1.0f};

  SpriteAnimationComponent() = default;
  SpriteAnimationComponent(const SpriteAnimationComponent &) = default;
};

struct VEGA_API NativeScriptComponent {
  ScriptableEntity *Instance = nullptr;

  ScriptableEntity *(*InstantiateScript)();
  void (*DestroyScript)(NativeScriptComponent *);

  template <typename T> void Bind() {
    InstantiateScript = []() {
      return static_cast<ScriptableEntity *>(new T());
    };
    DestroyScript = [](NativeScriptComponent *nsc) {
      delete nsc->Instance;
      nsc->Instance = nullptr;
    };
  }
};

} // namespace VEGA