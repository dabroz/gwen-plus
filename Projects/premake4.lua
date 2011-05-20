solution "GWEN"

	language "C++"
	location ( _ACTION )
	flags { "Unicode", "Symbols", "NoMinimalRebuild", "NoEditAndContinue", "NoManifest", "NoPCH", "No64BitChecks" }
	targetdir ( "../lib/" .. _ACTION )
	defines 
	{ 
		"GWEN_COMPILE",
		"GWEN_DLL"
	}

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
	
configuration "Debug"
	defines { "_DEBUG" }
	flags { "StaticRuntime" }

project "GWEN DLL"
	files { "../src/**.*", "../include/Gwen/**.*" }
	includedirs { "../include/" }
	kind "SharedLib"
	
	configuration "Release"
		targetname( "gwen" )
		
	configuration "Debug"
		targetname( "gwend" )
	
project "GWEN Static"
	files { "../src/**.*", "../include/Gwen/**.*" }
	flags { "StaticRuntime", "Symbols" }
	kind "StaticLib"
	includedirs { "../include/" }
	
	configuration "Release"
		targetname( "gwen_static" )
		
	configuration "Debug"
		targetname( "gwend_static" )