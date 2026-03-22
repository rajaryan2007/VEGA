#pragma once

#include "VEGA/Core/Timestep.h"
#include "entt.hpp"

namespace VEGA {

class Entity;
struct TransformComponent;
struct CameraComponent;
struct TagComponent;
struct SpriteRendererComponent;
struct NativeScriptComponent;

class VEGA_API Scene {
public:
  Scene();
  ~Scene();

  Entity CreateEntity(const std::string &name = std::string());

  void DestroyEntity(Entity entity);

  void OnViewportResize(u32 width, u32 height);

  void OnUpdate(Timestep ts);

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
  void OnComponentAdded<NativeScriptComponent>(Entity entity,
                                               NativeScriptComponent &components);

private:
  entt::registry m_registry;
  u32 m_ViewportWidth = 0, m_ViewportHeight = 0;

  friend class SceneSerializer;
  friend class Entity;
  friend class SceneHierarchyPanel;
};

} // namespace VEGA