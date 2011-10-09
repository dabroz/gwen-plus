dofile( "functions.lua" )

solution "GWEN"

	language "C++"
	location ( os.get() .. "/" .. _ACTION )
	flags { "Unicode", "Symbols", "NoMinimalRebuild", "NoEditAndContinue", "NoPCH", "No64BitChecks", "NoRTTI" }
	targetdir ( "../lib/" .. os.get() )
	libdirs { "../lib/", "../lib/" .. os.get() }

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
	uuid ( "74670653-3D57-A243-91B4-B2EEDF35DA95" )
	defines { "GWEN_COMPILE_DLL" }
	files { "../src/**.*", "../include/Gwen/**.*" }
	kind "SharedLib"
	
	configuration "Release"
		targetname( "gwen" )
		
	configuration "Debug"
		targetname( "gwend" )

project "GWEN Static"
	uuid ( "99E8E26E-4171-4a0a-B6D8-020A0E63E436" )
	defines { "GWEN_COMPILE_STATIC" }
	files { "../src/**.*", "../include/Gwen/**.*" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "gwen_static" )
		
	configuration "Debug"
		targetname( "gwend_static" )
		
project "UnitTest"
	uuid ( "00F7E527-468D-4b79-9A35-F3386C0CF7F9" )
	files { "../UnitTest/**.*" }
	flags { "Symbols" }
	kind "StaticLib"
	
	configuration "Release"
		targetname( "unittest" )
		
	configuration "Debug"
		targetname( "unittestd" )
		

--
-- Renderers
--

DefineRenderer( "OpenGL", {"../Renderers/OpenGL/OpenGL.cpp"} )
DefineRenderer( "OpenGL_DebugFont", { "../Renderers/OpenGL/OpenGL.cpp", "../Renderers/OpenGL/DebugFont/OpenGL_DebugFont.cpp" } )
DefineRenderer( "SFML", { "../Renderers/SFML/SFML.cpp" } )

if ( os.get() == "windows" ) then
	DefineRenderer( "DirectX9", { "../Renderers/DirectX9/DirectX9.cpp" } )
	DefineRenderer( "GDI", { "../Renderers/GDIPlus/GDIPlus.cpp", "../Renderers/GDIPlus/GDIPlusBuffered.cpp" } )
end

--
-- Samples
--

DefineSample( "SFML", { "../Samples/SFML/SFML.cpp" }, { "Renderer-SFML", "UnitTest", "GWEN Static" } )
DefineSample( "OpenGL", { "../Samples/OpenGL/OpenGLSample.cpp" }, { "Renderer-OpenGL", "GWEN Static", "UnitTest", "opengl32", "FreeImage" } )
DefineSample( "OpenGL_DebugFont", { "../Samples/OpenGL/OpenGLSample.cpp" }, { "GWEN Static", "UnitTest", "opengl32", "FreeImage" }, nil, { "USE_DEBUG_FONT" } )

if ( os.get() == "windows" ) then

	DefineSample( "DirectX9", { "../Samples/Direct3D/Direct3DSample.cpp" }, { "Renderer-DirectX9", "GWEN Static", "UnitTest" } )
	DefineSample( "WindowsGDI", { "../Samples/WindowsGDI/WindowsGDI.cpp" }, { "Renderer-GDI", "GWEN Static", "UnitTest" } )

end


