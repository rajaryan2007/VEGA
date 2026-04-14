#pragma once

#include "UHE/Core/Timestep.h"
#include "entt.hpp"
#include "UHE/Renderer/EditorCamera.h"

namespace UHE {

class Entity;
struct TransformComponent;
struct CameraComponent;
struct TagComponent;
struct SpriteRendererComponent;
struct SpriteAnimationComponent;
struct NativeScriptComponent;

class UHE_API Scene {
public:
  Scene();
  ~Scene();

  Entity CreateEntity(const std::string &name = std::string());

  void DestroyEntity(Entity entity);

  void OnViewportResize(u32 width, u32 height);

  void OnUpdateEditor(Timestep ts,EditorCamera& camera);
  void OnUpdateRuntime(Timestep ts);

  Entity GetPrimaryCameraEntity();
public:
  template <typename T> void OnComponentAdded(Entity entity, T &components);

  template <>
  void OnComponentAdded<TransformComponent>(Entity entity,
                                            TransformComponent &components);
  template <>
  void OnComponentAdded<CameraComponent>(Entity entity,
                                         CameraComponent &components);
  template <>
  void OnComponentAdded<TagComponent>(Entity entity, TagComponent &components);
  template <>
  void OnComponentAdded<SpriteRendererComponent>(
      Entity entity, SpriteRendererComponent &components);
  template <>
  void OnComponentAdded<SpriteAnimationComponent>(
      Entity entity, SpriteAnimationComponent &components);
  template <>
  void OnComponentAdded<NativeScriptComponent>(Entity entity,
                                               NativeScriptComponent &components);

private:
  void RenderSprites(Timestep ts);

  entt::registry m_registry;
  u32 m_ViewportWidth = 0, m_ViewportHeight = 0;

  friend class SceneSerializer;
  friend class Entity;
  friend class SceneHierarchyPanel;
};

} // namespace UHE