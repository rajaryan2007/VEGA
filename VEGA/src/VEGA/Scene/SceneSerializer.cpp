#include "vgpch.h"
#include "SceneSerializer.h"
#include "Entity.h"
#include "Components.h"
#include "VEGA/Utils/YamlUtils.h"
#include <fstream>

namespace VEGA {

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene) {
	}


	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "Entity" << YAML::Value << "2323232";//TODO enitity

		// Tag
		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent" << YAML::BeginMap;
			out << YAML::Key << "Tag" << YAML::Value
				<< entity.GetComponent<TagComponent>().Tag;
			out << YAML::EndMap;
		}

		// Transform
		if (entity.HasComponent<TransformComponent>())
		{
			auto& tc = entity.GetComponent<TransformComponent>();

			out << YAML::Key << "TransformComponent" << YAML::BeginMap;
			out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.Scale;
			out << YAML::EndMap;
		}

	
		if (entity.HasComponent<CameraComponent>())
		{
			auto& cc = entity.GetComponent<CameraComponent>();
			auto& cam = cc.Camera;

			out << YAML::Key << "CameraComponent" << YAML::BeginMap;

			out << YAML::Key << "ProjectionType" << YAML::Value << (int)cam.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << cam.GetProjectionFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << cam.GetProjectionNear();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << cam.GetProjectionFar();

			out << YAML::Key << "OrthographicSize" << YAML::Value << cam.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << cam.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << cam.GetOrthographicFarClip();

			out << YAML::Key << "Primary" << YAML::Value << cc.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cc.FixedAspectRatio;

			out << YAML::EndMap;
		}

		// Sprite
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			auto& src = entity.GetComponent<SpriteRendererComponent>();

			out << YAML::Key << "SpriteRendererComponent" << YAML::BeginMap;
			out << YAML::Key << "Color" << YAML::Value << src.Color;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::BeginSeq;

		auto view = m_Scene->m_registry.view<entt::entity>();
		for (auto entityID : view)
		{
			Entity entity{ entityID, m_Scene.get() };
			if (entity)
				SerializeEntity(out, entity);
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		if (!stream.is_open())
			return false;

		YAML::Node data = YAML::Load(stream);
		if (!data["Scene"])
			return false;

		auto entities = data["Entities"];
		if (!entities)
			return true;

		for (auto entityNode : entities)
		{
			std::string name = "Entity";

			auto tagNode = entityNode["TagComponent"];
			if (tagNode)
				name = tagNode["Tag"].as<std::string>();

			Entity entity = m_Scene->CreateEntity(name);

			// Transform
			auto transformNode = entityNode["TransformComponent"];
			if (transformNode)
			{
				auto& tc = entity.GetComponent<TransformComponent>();
				tc.Translation = transformNode["Translation"].as<glm::vec3>();
				tc.Rotation = transformNode["Rotation"].as<glm::vec3>();
				tc.Scale = transformNode["Scale"].as<glm::vec3>();
			}

			// Camera
			auto cameraNode = entityNode["CameraComponent"];
			if (cameraNode)
			{
				auto& cc = entity.AddComponent<CameraComponent>();
				auto& cam = cc.Camera;

				cam.SetProjectionType(
					(SceneCamera::ProjectionType)cameraNode["ProjectionType"].as<int>());

				cam.SetPerspectiveFOV(cameraNode["PerspectiveFOV"].as<float>());
				cam.SetPerpecstiveNear(cameraNode["PerspectiveNear"].as<float>());
				cam.SetPerspecstiveFar(cameraNode["PerspectiveFar"].as<float>());

				cam.SetOrthographicSize(cameraNode["OrthographicSize"].as<float>());
				cam.SetOrthoGraphicNearClip(cameraNode["OrthographicNear"].as<float>());
				cam.SetOrthoGraphicFarClip(cameraNode["OrthographicFar"].as<float>());

				cc.Primary = cameraNode["Primary"].as<bool>();
				cc.FixedAspectRatio = cameraNode["FixedAspectRatio"].as<bool>();
			}

			// Sprite
			auto spriteNode = entityNode["SpriteRendererComponent"];
			if (spriteNode)
			{
				auto& src = entity.AddComponent<SpriteRendererComponent>();
				src.Color = spriteNode["Color"].as<glm::vec4>();
			}
		}

		return true;
	}

}