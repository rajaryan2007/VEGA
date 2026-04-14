#include "VfsSystem.h"
#include "uhepch.h"
#include <filesystem>
#include <iostream>

namespace UHE {

void FileSystem::Initialize(const char *argv0) {
  fs::path exePath = fs::absolute(argv0).parent_path();
  bool foundSourceAssets = false;

  fs::path searchPath = exePath;
  while (searchPath.has_parent_path()) {
    if (fs::exists(searchPath / "UHE_EDITOR" / "assets")) {
      m_RootPath = searchPath / "UHE_EDITOR";
      foundSourceAssets = true;
      break;
    }

    fs::path parent = searchPath.parent_path();
    if (parent == searchPath)
      break;
    searchPath = parent;
  }

  if (!foundSourceAssets) {
    m_RootPath = exePath;
    if (!fs::exists(m_RootPath / "assets")) {
      std::cerr << "[UHE::FileSystem] WARNING: 'assets' folder not found at: "
                << m_RootPath.string() << std::endl;
    }
  }
}

std::string FileSystem::Resolve(const std::string &virtualPath) {
  return (m_RootPath / "assets" / virtualPath).string();
}

} // namespace UHE
