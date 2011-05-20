solution "GWEN"

	language "C++"
	location ( "Projects/" .. _ACTION )
	flags { "Unicode", "Symbols", "NoMinimalRebuild", "NoEditAndContinue", "NoManifest", "NoPCH", "No64BitChecks" }
	targetdir ( "lib" )
	defines 
	{ 
		"GWEN_COMPILE",
	}

	configurations
	{ 
		"Release-DLL",
		"Debug-DLL",
		"Release-Static",
		"Debug-Static",
	}
	
	-- Multithreaded compiling
	if _ACTION == "vs2010" or _ACTION=="vs2008" then
		buildoptions { "/MP"  }
	end 


configuration "Release-DLL"
	defines { "NDEBUG", "GWEN_DLL" }
	flags{ "Optimize", "FloatFast" }
	kind "SharedLib"
	targetname( "gwen" )
	
configuration "Debug-DLL"
	defines { "_DEBUG", "GWEN_DLL" }
	flags { "StaticRuntime" }
	kind "SharedLib"
	targetname( "gwend" )
	
configuration "Release-Static"
	defines { "NDEBUG", "GWEN_DLL" }
	flags{ "Optimize", "FloatFast" }
	kind "StaticLib"
	targetname( "gwen_static" )
	
configuration "Debug-Static"
	defines { "_DEBUG", "GWEN_DLL" }
	flags { "StaticRuntime", "Symbols" }
	kind "StaticLib"
	targetname( "gwend_static" )


-- SUBPROJECTS

project "GWEN"
	files { "src/**.*", "include/Gwen/**.*" }
	includedirs { "include/" }