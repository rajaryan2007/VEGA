#pragma once

#include "VEGA.h"
#include "VEGA/Core.h"
#include "VEGA/Scene/Scene.h"
#include "VEGA/Scene/Entity.h"

namespace VEGA {
	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);

		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
