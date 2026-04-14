#pragma once

#include <glm/glm.hpp>

namespace UHE {
	namespace Math {
		bool UHE_API DecomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale);
	}
}
