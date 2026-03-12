#pragma once

#include "VEGA/Core/Timestep.h"
#include "entt.hpp"



namespace VEGA
{
	 class Scene
	 {
	 public:
		 Scene();
		 ~Scene();

		 entt::entity CreateEntity();

		 entt::registry& Getregistry()   { return m_registry; }

		 void OnUpdate(Timestep ts);
	 private:
		 entt::registry m_registry;
	 };
}