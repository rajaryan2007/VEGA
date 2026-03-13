#pragma once 
#include "vgpch.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "VEGA/Core/Timestep.h"
#include "glm/glm.hpp"


namespace VEGA {
struct TransformComponent {
  glm::mat4 Transform{1.0f};

  TransformComponent() = default;
  TransformComponent(const TransformComponent &) = default;

  TransformComponent(const glm::mat4 &transform) : Transform(transform) {}

  operator glm::mat4 &() { return Transform; }
  operator const glm::mat4 &() const { return Transform; }
};
struct SpriteRendererComponent {
  glm::vec4 Color{1.0f};

  SpriteRendererComponent() = default;
  SpriteRendererComponent(const SpriteRendererComponent &) = default;
  SpriteRendererComponent(const glm::vec4 &color) : Color(color) {}
};
struct TagComponent {
  std::string Tag;

  TagComponent() = default;
  TagComponent(const TagComponent &) = default;
  TagComponent(const std::string &tag) : Tag(tag) {}
};

struct CameraComponent {
  SceneCamera Camera;
  bool Primary = true;
  bool FixedAspectRatio = false;

  CameraComponent() = default;
  CameraComponent(const CameraComponent &) = default;
};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		std::function<ScriptableEntity*()> InstantiateFunction;
		std::function<void(NativeScriptComponent*)> DestroyInstanceFunction;

		std::function<void(ScriptableEntity*)> OnCreateFunction;
		std::function<void(ScriptableEntity*)> OnDestroyFunction;
		std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyInstanceFunction = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };

			OnCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) { ((T*)instance)->OnUpdate(ts); };
		}
	};

} // namespace VEGA