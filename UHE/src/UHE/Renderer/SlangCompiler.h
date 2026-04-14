#pragma once
#include "UHE/Core/Core.h"
#include <string>
#include <unordered_map>

typedef unsigned int GLenum;

namespace UHE {
	class UHE_API SlangCompiler {
	public:
		static std::unordered_map<GLenum, std::string> CompileToGLSL(const std::string& filepath);
	};
}
