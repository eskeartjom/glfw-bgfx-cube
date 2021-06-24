project "Demo"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

	

    files
    {
        "Source/**.h",
        "Source/**.cpp"
    }

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	links
	{
		"glfw",
		"bgfx",
		"bx",
		"bimg"
	}
	
	filter "system:windows"
		systemversion "latest"
		includedirs
		{
			"src",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.bgfx}",
			"%{IncludeDir.bx}",
			"%{IncludeDir.bimg}",
			"%{IncludeDir.bx}/compat/msvc",
		}


	filter "system:macosx"
		sysincludedirs
		{
			"src",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.bgfx}",
			"%{IncludeDir.bx}",
			"%{IncludeDir.bimg}",
			"%{IncludeDir.bx}/compat/msvc",
		}

		links
		{
			"QuartzCore.framework",
			"Metal.framework",
			"Cocoa.framework",
			"IOKit.framework",
			"CoreVideo.framework",
		}

	filter "system:linux"
		includedirs
		{
			"src",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.bgfx}",
			"%{IncludeDir.bx}",
			"%{IncludeDir.bimg}",
			"%{IncludeDir.bx}/compat/msvc",
		}

		links
		{ 
			"dl",
			"GL",
			"pthread",
			"X11"
		}
		
	filter "configurations:Debug"
		defines "__DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "__RELEASE"
		runtime "Release"
		optimize "on"


	filter "configurations:Dist"
		defines "__DIST"
		runtime "Release"
		optimize "on"