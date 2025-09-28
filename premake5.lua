workspace "VEGA"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- VEGA Engine Library Project
project "VEGA"
    location "VEGA"
    kind "SharedLib"
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
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" } -- Added for Unicode support in spdlog

        defines
        {
            "VG_PLATFORM_WINDOWS",
            "VG_BUILD_DLL",
            "WINDLL"
        }

        postbuildcommands
        {
            -- Copy the DLL to the Sandbox's output directory for easy execution
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "VG_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "VG_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "VG_DIST"
        optimize "On"

-- Sandbox Application Project
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

    -- Added to ensure VEGA is built before Sandbox
    dependson { "VEGA" }

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" } -- For Unicode support in spdlog

        defines
        {
            "VG_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "VG_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "VG_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "VG_DIST"
        optimize "On"
