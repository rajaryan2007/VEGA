#pragma once

#include "VEGA/Core/Timestep.h"
#include "entt.hpp"

namespace VEGA {

class Entity;
class VEGA_API Scene {
public:
  Scene();
  ~Scene();

  Entity CreateEntity(const std::string &name = std::string());

  void DestroyEntity(Entity entity);

  void OnViewportResize(u32 width, u32 height);

  void OnUpdate(Timestep ts);

private:
  template <typename T> void OnComponentAdded(Entity entity, T &components);

private:
  entt::registry m_registry;
  u32 m_ViewportWidth = 0, m_ViewportHeight = 0;

  friend class Entity;
  friend class SceneHierarchyPanel;
};

} // namespace VEGA