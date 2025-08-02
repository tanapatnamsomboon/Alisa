-- ~/Alisa/premake5.lua

project "Alisa"
	kind "StaticLib"
	language "C++"
	cppdialect "C++23"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "src/pch.cpp"

	files
	{
		"include/**.h",
		"src/**.cpp",
	}
	
	includedirs
	{
		"include",
		"%{wks.location}/vendor/spdlog/include",
        "%{wks.location}/vendor/magic_enum/include",
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions
		{
			"/utf-8",
		}
		
	filter "configurations:Debug"
		defines "ALISA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ALISA_RELEASE"
		runtime "Release"
		optimize "on"
