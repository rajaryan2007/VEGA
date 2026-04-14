#pragma once

#include "UHE.h"
#include "UHE/Core/Core.h"
#include "UHE/Scene/Scene.h"
#include "UHE/Scene/Entity.h"

namespace UHE {
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
