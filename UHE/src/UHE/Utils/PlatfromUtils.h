#pragma once
#include <string>


namespace UHE {
	class UHE_API FileDialogs
	{
	public:
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}
