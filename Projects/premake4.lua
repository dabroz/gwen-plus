solution "GWEN"

	language "C++"
	location ( _ACTION )
	flags { "Unicode", "Symbols", "NoMinimalRebuild", "NoEditAndContinue", "NoPCH", "No64BitChecks" }
	targetdir ( "../lib/" .. _ACTION )
	libdirs { "../lib/" .. _ACTION }

	configurations
	{ 
		"Release",
		"Debug"
	}
	
	-- Multithreaded compiling
	if _ACTION == "vs2010" or _ACTION=="vs2008" then
		buildoptions { "/MP"  }
	end 

configuration "Release"
	defines { "NDEBUG" }
	flags{ "Optimize", "FloatFast" }
	includedirs { "../include/" }
	
configuration "Debug"
	defines { "_DEBUG" }
	includedirs { "../include/" }

project "GWEN DLL"
	defines { "GWEN_COMPILE_DLL" }
	files { "../src/**.*", "../include/Gwen/**.*" }
	kind "SharedLib"
	
	configuration "Release"
		targetname( "gwen" )
		
	configuration "Debug"
		targetname( "gwend" )
	
project "GWEN Static"
	defines { "GWEN_COMPILE_STATIC" }
	files { "../src/**.*", "../include/Gwen/**.*" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "gwen_static" )
		
	configuration "Debug"
		targetname( "gwend_static" )
		
project "UnitTest"
	files { "../unittest/**.*" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "unittest" )
		
	configuration "Debug"
		targetname( "unittestd" )
	
project "Renderer-DirectX9"
	files { "../renderers/DirectX9/DirectX9.cpp" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "GWEN-Renderer-DirectX9" )
		
	configuration "Debug"
		targetname( "GWEN-Renderer-DirectX9d" )

project "Renderer-GDI"
	files { "../renderers/GDIPlus/GDIPlus.cpp" }
	files { "../renderers/GDIPlus/GDIPlusBuffered.cpp" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "GWEN-Renderer-GDI" )
		
	configuration "Debug"
		targetname( "GWEN-Renderer-GDI" )
		
project "Sample-DirectX9"
	targetdir ( "../bin" )
	debugdir ( "../bin" )
	files { "../Samples/Direct3D/Direct3DSample.cpp" }
	kind "WindowedApp"
	
	links { "Renderer-DirectX9", "GWEN Static", "UnitTest" }

	configuration "Release"
		targetname( "DX9Sample" )
		
	configuration "Debug"
		targetname( "DX9Sample_D" )

project "Sample-WindowsGDI"
	targetdir ( "../bin" )
	debugdir ( "../bin" )
	files { "../Samples/WindowsGDI/WindowsGDI.cpp" }
	kind "WindowedApp"
	links { "Renderer-GDI", "GWEN Static", "UnitTest" }	
	
	configuration "Release"
		targetname( "GDISample" )
		
	configuration "Debug"
		targetname( "GDISample_D" )