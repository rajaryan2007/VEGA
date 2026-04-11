#include "VfsSystem.h"
#include "vgpch.h"
#include <filesystem>
#include <iostream>

namespace VEGA {

void FileSystem::Initialize(const char *argv0) {
  fs::path exePath = fs::absolute(argv0).parent_path();
  bool foundSourceAssets = false;

  fs::path searchPath = exePath;
  while (searchPath.has_parent_path()) {
    if (fs::exists(searchPath / "VEGA_EDITOR" / "assets")) {
      m_RootPath = searchPath / "VEGA_EDITOR";
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
      std::cerr << "[VEGA::FileSystem] WARNING: 'assets' folder not found at: "
                << m_RootPath.string() << std::endl;
    }
  }
}

std::string FileSystem::Resolve(const std::string &virtualPath) {
  return (m_RootPath / "assets" / virtualPath).string();
}

} // namespace VEGA
