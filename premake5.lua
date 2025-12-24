workspace "VEGA"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories
IncludeDir = {}
IncludeDir["GLFW"] = "VEGA/vendor/GLFW/include"
IncludeDir["Glad"] = "VEGA/vendor/Glad/include"
IncludeDir["ImGui"] = "VEGA/vendor/imgui"
IncludeDir["glm"] = "VEGA/vendor/glm"

include "VEGA/vendor/GLFW"
include "VEGA/vendor/Glad"
include "VEGA/vendor/imgui"

project "VEGA"
    location "VEGA"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "vgpch.h"
    pchsource "VEGA/src/vgpch.cpp"
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }
    links
    {
         "GLFW",
         "Glad",
         "ImGui",
         "opengl32.lib"
    }


    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" }

        defines
        {
            "VG_PLATFORM_WINDOWS",
            "VG_BUILD_DLL",
            "WINDLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {

            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "VG_DEBUG"
        buildoptions"/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "VG_RELEASE"
        buildoptions"/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "VG_DIST"
        buildoptions"/MD"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "VEGA/vendor/spdlog/include",
        "VEGA/src",
        "%{IncludeDir.glm}"
    }

    links
    {
        "VEGA"
    }


    dependson { "VEGA" }

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" }

        defines
        {
            "VG_PLATFORM_WINDOWS"
        }

 filter "configurations:Debug"
    defines "VG_DEBUG"
    buildoptions "/MDd"
    symbols "On"

filter "configurations:Release"
    defines "VG_RELEASE"
    buildoptions "/MD"
    optimize "On"

filter "configurations:Dist"
    defines "VG_DIST"
    buildoptions "/MD"
    optimize "On"
        defines "VG_DIST"
        buildoptions"/MD"
        optimize "On"
