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

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);

	private:
 		void DrawEntityNode(Entity entity);

		void DrawComponents(Entity entity);

		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
