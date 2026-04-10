#pragma once
#include "VEGA/Core.h"
#include <string>
#include <unordered_map>

typedef unsigned int GLenum;

namespace VEGA {
	class VEGA_API SlangCompiler {
	public:
		static std::unordered_map<GLenum, std::string> CompileToGLSL(const std::string& filepath);
	};
}
