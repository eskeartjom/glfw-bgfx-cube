workspace "glfw-bgfx"
    architecture "x86_64"
    startproject "Demo"

    configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	platforms 
	{ 
		"x64" 
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["glfw"] = "%{wks.location}/Demo/Dependencies/glfw/include"
	IncludeDir["bgfx"] = "%{wks.location}/Demo/Dependencies/bgfx/include"
	IncludeDir["bx"] = "%{wks.location}/Demo/Dependencies/bx/include"
	IncludeDir["bimg"] = "%{wks.location}/Demo/Dependencies/bimg/include"

	group "Dependencies"
		include "Demo/Dependencies/glfw"
		include "Demo/Dependencies/bgfx"
		include "Demo/Dependencies/bx"
		include "Demo/Dependencies/bimg"
	group ""

	include "Demo"
