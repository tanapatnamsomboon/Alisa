-- ~/Samples/HelloAlisa/premake5.lua

project "HelloAlisa"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++23"
	staticruntime "off"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"src/**.h",
		"src/**.cpp",
	}
	
	includedirs
	{
		"src",
		"%{wks.location}/Alisa/include",
		"%{wks.location}/vendor/spdlog/include",
        "%{wks.location}/vendor/magic_enum/include",
	}
	
	links
	{
		"Alisa",
	}
	
	filter "system:windows"
		systemversion "latest"
		buildoptions
		{
			"/utf-8",
		}
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
