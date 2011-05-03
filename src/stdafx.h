// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
// Pat: Making unix compatible.
#ifdef _WIN32

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

// Pat: no api specific min max usage. use GwenUtil_Min and GwenUtil_Max
#define NOMINMAX
#include <windows.h>

#define GwenUtil_VSNPrintFSafe( _DstBuf, _DstSize, _MaxCount, _Format, _ArgList ) vsnprintf_s( _DstBuf, _DstSize, _MaxCount, _Format, _ArgList )
#define GwenUtil_VSWPrintFSafe( _DstBuf, _SizeInWords, _Format, _ArgList ) vswprintf_s( _DstBuf, _SizeInWords, _Format, _ArgList )
#define GwenUtil_OutputDebugCharString( lpOutputString ) OutputDebugStringA( lpOutputString )
#define GwenUtil_OutputDebugWideString( lpOutputString ) OutputDebugStringW( lpOutputString )
#define GwenUtil_WideStringToFloat( _Str ) _wtof( _Str )

#elif defined(__APPLE__)

#include <CoreFoundation/CoreFoundation.h>

// Pat: to avoid a massive rewrite mimicing windows/msvc std / api functions
#define GwenUtil_VSNPrintFSafe( _DstBuf, _DstSize, _MaxCount, _Format, _ArgList ) vsnprintf( _DstBuf, _DstSize, _Format, _ArgList )
#define GwenUtil_VSWPrintFSafe( _DstBuf, _SizeInWords, _Format, _ArgList ) vswprintf( _DstBuf, _SizeInWords, _Format, _ArgList )
#define GwenUtil_OutputDebugCharString( lpOutputString ) //printf( lpOutputString )
#define GwenUtil_OutputDebugWideString( lpOutputString ) //wprintf( lpOutputString  )
#define GwenUtil_WideStringToFloat( _Str ) wcstof(_Str, NULL)

#elif defined(__linux__)

#define GwenUtil_VSNPrintFSafe( _DstBuf, _DstSize, _MaxCount, _Format, _ArgList ) vsnprintf( _DstBuf, _DstSize, _Format, _ArgList )
#define GwenUtil_VSWPrintFSafe( _DstBuf, _SizeInWords, _Format, _ArgList ) vswprintf( _DstBuf, _SizeInWords, _Format, _ArgList )
#define GwenUtil_OutputDebugCharString( lpOutputString ) //printf( lpOutputString )
#define GwenUtil_OutputDebugWideString( lpOutputString ) //wprintf( lpOutputString  )
#define GwenUtil_WideStringToFloat( _Str ) wcstof(_Str, NULL)

#else

#error MUST_IMPLEMENT_PLATFORM

#endif

//shared
#define GwenUtil_VSWPrintFSafeSized( _DstBuf_ARRAY_, _Format, _ArgList ) GwenUtil_VSWPrintFSafe( _DstBuf_ARRAY_, sizeof( _DstBuf_ARRAY_ ) / sizeof( wchar_t ), _Format, _ArgList )
// C RunTime Header Files
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <memory.h>
#include <algorithm>

// Pat: min max not tied to platform api.
#define GwenUtil_Min( a, b ) ( ( (a) < (b) ) ? (a) : (b) )
#define GwenUtil_Max( a, b ) ( ( (a) > (b) ) ? (a) : (b) )

// TODO: reference additional headers your program requires here
