#include "vgpch.h"
#include "Scene.h"
#include <glm/glm.hpp>

#include "Components.h"
#include "VEGA/Renderer2D/Renderer2D.h"
#include "Entity.h"

namespace VEGA
{



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

   

	VEGA::Entity Scene::CreateEntity(const std::string& name /*= std::string()*/)
	{
		Entity entity = { m_registry.create(),this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
        
		return entity;
	}

    
    

    void Scene::OnViewportResize(u32 width, u32 height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        auto view = m_registry.view<CameraComponent>();
        for (auto entity : view) {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.FixedAspectRatio)
            {
                cameraComponent.Camera.SetViewportSize(width, height);
            }
        }
    }

	void Scene::OnUpdate(Timestep ts)
	{
        Camera* mainCamera = nullptr;
        glm::mat4* cameraTransform = nullptr;
        
        auto view = m_registry.view<TransformComponent, CameraComponent>();
        for (auto entity : view)
        {
            auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

            if (camera.Primary)
            {
                mainCamera = &camera.Camera;
                cameraTransform = &transform.Transform;
                break;
            }
        }

        if (mainCamera)
        {
            Renderer2D::BeginScene(*mainCamera, *cameraTransform);

            auto group = m_registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::DrawQuad(transform.Transform, sprite.Color);
            }

            Renderer2D::EndScene();
        }

	}      

}
