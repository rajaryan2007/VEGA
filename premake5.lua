workspace "VEGA"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories
IncludeDir = {}
IncludeDir["GLFW"] = "VEGA/vendor/GLFW/include"

include "VEGA/vendor/GLFW"

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
        "%{IncludeDir.GLFW}"

    }
    links
    {
         "GLFW",
         "opengl32.lib"
    }


    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" }

        defines
        {
            "VG_PLATFORM_WINDOWS",
            "VG_BUILD_DLL",
            "WINDLL"
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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "VEGA/vendor/spdlog/include",
        "VEGA/src"
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
