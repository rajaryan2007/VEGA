#include "Scene.h"
#include "uhepch.h"
#include <glm/glm.hpp>

#include "Components.h"
#include "Entity.h"
#include "UHE/Renderer2D/Renderer2D.h"
#include "UHE/Renderer2D/SubTexture2D.h"

#include <box2d/box2d.h>



namespace UHE {

Scene::Scene() {
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
  // auto group =
  // m_registry.group<TransformComponent>(entt::get<MeshComponent>);
  //
  // for (auto entity : group)
  // {
  //     auto& [transform, mesh] = group.get<TransformComponent,
  //     MeshComponent>(entity);
  // }
}

Scene::~Scene() {}

UHE::Entity Scene::CreateEntity(const std::string &name /*= std::string()*/) {
  Entity entity = {m_registry.create(), this};
  entity.AddComponent<TransformComponent>();
  auto &tag = entity.AddComponent<TagComponent>();
  tag.Tag = name.empty() ? "Entity" : name;

  return entity;
}

void Scene::DestroyEntity(Entity entity) { m_registry.destroy(entity); }

void Scene::OnViewportResize(u32 width, u32 height) {
  m_ViewportWidth = width;
  m_ViewportHeight = height;

  auto view = m_registry.view<CameraComponent>();
  for (auto entity : view) {
    auto &cameraComponent = view.get<CameraComponent>(entity);
    if (!cameraComponent.FixedAspectRatio) {
      cameraComponent.Camera.SetViewportSize(width, height);
    }
  }
}

void Scene::OnUpdateEditor(Timestep ts, EditorCamera &camera) {
  m_registry.view<NativeScriptComponent>().each([=](auto entity, auto &nsc) {
    if (!nsc.Instance) {
      nsc.Instance = nsc.InstantiateScript();
      nsc.Instance->m_Entity = Entity{entity, this};
      nsc.Instance->OnCreate();
    }
    nsc.Instance->OnUpdate(ts);
  });

  Renderer2D::BeginScene(camera);
  RenderSprites(ts);
  Renderer2D::EndScene();
}

void Scene::RenderSprites(Timestep ts) {
  auto animView = m_registry.view<SpriteAnimationComponent>();
  for (auto entity : animView) {
    auto &comp = animView.get<SpriteAnimationComponent>(entity);
    comp.Animation.Tick(ts);
  }

  auto spriteView =
      m_registry.view<TransformComponent, SpriteRendererComponent>();
  for (auto entityID : spriteView) {
    auto [transform, sprite] =
        spriteView.get<TransformComponent, SpriteRendererComponent>(entityID);

    Renderer2D::DrawSprite(transform.GetTransform(), sprite, (i32)entityID);
  }

  auto animOnlyView =
      m_registry.view<TransformComponent, SpriteAnimationComponent>();
  for (auto entityID : animOnlyView) {
    if (m_registry.all_of<SpriteRendererComponent>(entityID))
      continue;

    auto [transform, comp] =
        animOnlyView.get<TransformComponent, SpriteAnimationComponent>(
            entityID);

    Ref<SubTexture2D> overrideSubTex = comp.Animation.GetCurrentFrame();
    if (overrideSubTex) {
      Renderer2D::DrawQuad(transform.GetTransform(), overrideSubTex, 1.0f,
                           comp.Color);
    }
  }
}

void Scene::OnUpdateRuntime(Timestep ts) {

  {

    m_registry.view<NativeScriptComponent>().each([=](auto entity, auto &nsc) {
      if (!nsc.Instance) {
        nsc.Instance = nsc.InstantiateScript();
        nsc.Instance->m_Entity = Entity{entity, this};
        nsc.Instance->OnCreate();
      }
      nsc.Instance->OnUpdate(ts);
    });
  }

  Camera *mainCamera = nullptr;
  glm::mat4 cameraTransform;

  auto view = m_registry.view<TransformComponent, CameraComponent>();
  for (auto entity : view) {
    auto [transform, camera] =
        view.get<TransformComponent, CameraComponent>(entity);

    if (camera.Primary) {
      mainCamera = &camera.Camera;
      cameraTransform = transform.GetTransform();
      break;
    }
  }

  if (mainCamera) {
    Renderer2D::BeginScene(*mainCamera, cameraTransform);
    RenderSprites(ts);
    Renderer2D::EndScene();
  }
}


void Scene::OnRuntimeStart()
{
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, -9.8f };

	m_PhysicsWorldId = b2CreateWorld(&worldDef);
}


void Scene::OnRuntimeStop()
{
	if (b2World_IsValid(m_PhysicsWorldId)) {
		b2DestroyWorld(m_PhysicsWorldId);
		m_PhysicsWorldId = b2_nullWorldId;
	}
}

Entity Scene::GetPrimaryCameraEntity() {
  auto view = m_registry.view<TransformComponent, CameraComponent>();
  for (auto entity : view) {
    const auto &camera = view.get<CameraComponent>(entity);
    if (camera.Primary)
      return Entity{entity, this};
  }
  return {};
}

template <typename T>
void Scene::OnComponentAdded(Entity entity, T &components) {
  static_assert(sizeof(T) == 0, "Only specialized components can be added!");
}

template <>
void Scene::OnComponentAdded<TransformComponent>(
    Entity entity, TransformComponent &components) {}
template <>
void Scene::OnComponentAdded<CameraComponent>(Entity entity,
                                              CameraComponent &components) {
  components.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
}

template <>
void Scene::OnComponentAdded<TagComponent>(Entity entity,
                                           TagComponent &components) {}

template <>
void Scene::OnComponentAdded<SpriteRendererComponent>(
    Entity entity, SpriteRendererComponent &components) {}

template <>
void Scene::OnComponentAdded<SpriteAnimationComponent>(
    Entity entity, SpriteAnimationComponent &components) {}

template <>
void Scene::OnComponentAdded<NativeScriptComponent>(
    Entity entity, NativeScriptComponent &components) {}

template void
Scene::OnComponentAdded<TransformComponent>(Entity entity,
                                            TransformComponent &components);
template void
Scene::OnComponentAdded<CameraComponent>(Entity entity,
                                         CameraComponent &components);
template void Scene::OnComponentAdded<TagComponent>(Entity entity,
                                                    TagComponent &components);
template void Scene::OnComponentAdded<SpriteRendererComponent>(
    Entity entity, SpriteRendererComponent &components);
template void Scene::OnComponentAdded<SpriteAnimationComponent>(
    Entity entity, SpriteAnimationComponent &components);
template void Scene::OnComponentAdded<NativeScriptComponent>(
    Entity entity, NativeScriptComponent &components);

} // namespace UHE
