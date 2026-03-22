#pragma once
#include <string>


namespace VEGA {
	class VEGA_API FileDialogs
	{
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}
