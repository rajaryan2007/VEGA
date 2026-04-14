#pragma once

#include <filesystem>
#include <string>
#include "UHE/Core/Core.h"

namespace fs = std::filesystem;

namespace UHE {
	class UHE_API FileSystem {
	public:
		
		static FileSystem& Get() {
			static FileSystem instance;
			return instance;
		}

		void Initialize(const char* argv0);

	
		std::string Resolve(const std::string& virtualPath);

		
		const fs::path& GetRootPath() const { return m_RootPath; }

	private:
		FileSystem() = default;
		std::filesystem::path m_RootPath;
	};
}