/*
	GWEN
	Copyright (c) 2009 Facepunch Studios
	See license in Gwen.h
*/


#pragma once
#include "Gwen/Gwen.h"
#include "Gwen/Align.h"
#include "Gwen/Utility.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/ListBox.h"

class UnitTest;

#ifdef _MSC_VER
#	ifdef GWEN_DLL
#		ifdef NDEBUG
#			pragma comment ( lib, "gwen-unittest_dll.lib" )
#		else
#			pragma comment ( lib, "gwend-unittest_dll.lib" )
#		endif
#	else
#		ifdef NDEBUG
#			pragma comment ( lib, "gwen-unittest_static.lib" )
#		else
#			pragma comment ( lib, "gwend-unittest_static.lib" )
#		endif
#	endif
#endif


class GUnit : public Gwen::Controls::Base
{
	public:

		GWEN_CONTROL_INLINE( GUnit, Gwen::Controls::Base )
		{
			m_pUnitTest = NULL;
		}

		void SetUnitTest( UnitTest* u ){ m_pUnitTest = u; }

		void UnitPrint( const Gwen::UnicodeString& str );
		void UnitPrint( const Gwen::String& str );


		UnitTest* m_pUnitTest;
};

class UnitTest : public Gwen::Controls::WindowControl
{
	public:

		GWEN_CONTROL( UnitTest, Gwen::Controls::WindowControl );

		void PrintText( const Gwen::UnicodeString& str );


	private:

		Gwen::Controls::TabControl*	m_TabControl;
		Gwen::Controls::ListBox*	m_TextOutput;

};

#define DEFINE_UNIT_TEST( name, displayname ) GUnit* RegisterUnitTest_##name( Gwen::Controls::TabControl* tab ){ GUnit* u = new name( tab ); tab->AddPage( displayname, u ); return u; }
