/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

#ifdef _WIN32

#	ifdef GWEN_DLL
#		ifdef GWEN_COMPILE
#			ifdef __GNUC__
#				define GWEN_EXPORT __attribute__((dllexport))
#			else
#				define GWEN_EXPORT __declspec(dllexport)
#			endif
#		else
#			ifdef __GNUC__
#				define GWEN_EXPORT __attribute__((dllimport))
#			else
#				define GWEN_EXPORT __declspec(dllimport)
#			endif
#			ifndef _DEBUG
#				pragma comment ( lib, "gwen.lib" )
#			else
#				pragma comment ( lib, "gwend.lib" )
#			endif
#		endif
#	else
#		define GWEN_EXPORT
#		ifndef GWEN_COMPILE
#			ifndef _DEBUG
#				pragma comment ( lib, "gwen_static.lib" )
#			else
#				pragma comment ( lib, "gwend_static.lib" )
#			endif
#		endif
#	endif

#else

#	if defined(__GNUC__) && __GNUC__ >= 4
#		define GWEN_EXPORT __attribute__((visibility("default")))
#	else
#		define GWEN_EXPORT
#	endif

#endif

#ifdef _MSC_VER

#define GWEN_FINLINE __forceinline
#define GWEN_PURE_INTERFACE __declspec(novtable)

#elif defined(__GNUC__)

#define GWEN_FINLINE __attribute__((always_inline)) inline
#define GWEN_PUREINTERFACE 

#else

#define GWEN_FINLINE inline
#define GWEN_PUREINTERFACE 

#endif