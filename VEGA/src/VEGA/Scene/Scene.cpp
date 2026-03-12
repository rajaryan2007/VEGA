#include "vgpch.h"
#include "Scene.h"
#include <glm/glm.hpp>

#include "Components.h"
#include "VEGA/Renderer2D/Renderer2D.h"

namespace VEGA
{

    struct TransformComponent
    {
        glm::mat4 Transform;

        TransformComponent() = default;
        TransformComponent(const glm::mat4& transform)
            : Transform(transform) {
        }

        operator const glm::mat4& () const { return Transform; }
    };

    struct MeshComponent
    {
        u32 textureId;
    };

    Scene::Scene()
    {
       // entt::entity entity = m_registry.create();
       //
       // m_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
       //
       // if (m_registry.all_of<TransformComponent>(entity))
       // {
       //     auto& transform = m_registry.get<TransformComponent>(entity);
       // }
       //
       // auto view = m_registry.view<TransformComponent>();
       //
       // for (auto entity : view)
       // {
       //     auto& transform = view.get<TransformComponent>(entity);
       // }
       //
       // auto group = m_registry.group<TransformComponent>(entt::get<MeshComponent>);
       //
       // for (auto entity : group)
       // {
       //     auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
       // }
    }

    Scene::~Scene()
    {
    }

    entt::entity Scene::CreateEntity()
    {
        return m_registry.create();
    }

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
            Renderer2D::DrawQuad(transform, sprite.Color);
		}

        

	}

}
