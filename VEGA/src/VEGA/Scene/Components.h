#pragma once
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "VEGA/Core/Timestep.h"
#include "glm/glm.hpp"
#include "vgpch.h"
#include "glm/gtc/matrix_transform.hpp"


namespace VEGA {
struct VEGA_API TransformComponent {
    glm::vec3 Translation{0.0f};
    glm::vec3 Rotation{0.0f};   // assumed in degrees
    glm::vec3 Scale{1.0f};

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;

    TransformComponent(const glm::vec3& translation)
        : Translation(translation) {}

    glm::mat4 GetTransform() const
    {
        glm::mat4 rotation =
            glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), {1, 0, 0}) *
            glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), {0, 1, 0}) *
            glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), {0, 0, 1});

        return glm::translate(glm::mat4(1.0f), Translation)
             * rotation
             * glm::scale(glm::mat4(1.0f), Scale);
    }
};
struct VEGA_API SpriteRendererComponent {
  glm::vec4 Color{1.0f};

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