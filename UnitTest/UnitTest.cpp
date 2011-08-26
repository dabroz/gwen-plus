/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Controls/DockedTabControl.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Platform.h"

using namespace Gwen;

#define ADD_UNIT_TEST( name, parent )\
	GUnit* RegisterUnitTest_##name( Gwen::Controls::Base* tab );\
	{\
		GUnit* test = RegisterUnitTest_##name( parent );\
		test->SetUnitTest( this );\
		parent->GetTabControl()->AddPage( #name, test );\
	}\

Gwen::Controls::TabButton* pButton = NULL;

GWEN_CONTROL_CONSTRUCTOR( UnitTest )
{
	Dock( Pos::Fill );
	SetSize( 1024, 768 );

	m_TextOutput = new Controls::ListBox( GetRight() );
	pButton = GetRight()->GetTabControl()->AddPage( "Output", m_TextOutput );
	GetRight()->SetWidth( 250 );

	m_StatusBar = new Controls::StatusBar( this );
	m_StatusBar->Dock( Pos::Bottom );

	ADD_UNIT_TEST( TreeControl, GetBottom() );
	ADD_UNIT_TEST( Button, GetBottom() );
	ADD_UNIT_TEST( Label, GetBottom() );
	ADD_UNIT_TEST( Properties, GetBottom() );
	ADD_UNIT_TEST( TabControl, GetBottom() );
	ADD_UNIT_TEST( ScrollControl, GetBottom() );	
	ADD_UNIT_TEST( ComboBox, GetBottom() );
	ADD_UNIT_TEST( TextBox, GetBottom() );
	ADD_UNIT_TEST( ListBox, GetBottom() );
	ADD_UNIT_TEST( Slider, GetBottom() );
	ADD_UNIT_TEST( ProgressBar, GetBottom() );
	
	ADD_UNIT_TEST( ImagePanel, GetBottom()->GetTop() );
	ADD_UNIT_TEST( Numeric, GetBottom()->GetTop() );
	ADD_UNIT_TEST( MenuStrip, GetBottom()->GetTop() );
	ADD_UNIT_TEST( CrossSplitter, GetBottom()->GetTop() );
	ADD_UNIT_TEST( PanelListPanel, GetBottom()->GetTop() );
	ADD_UNIT_TEST( GroupBox, GetBottom()->GetTop() );
	ADD_UNIT_TEST( StatusBar, GetBottom()->GetTop() );
	ADD_UNIT_TEST( RadioButton, GetBottom()->GetTop() );

	ADD_UNIT_TEST( Checkbox, GetBottom()->GetTop()->GetLeft() );

	GetBottom()->Dock( Pos::Fill );
	m_StatusBar->SendToBack();
	
	PrintText( L"Unit Test Started.\n" );

	m_fLastSecond = Gwen::Platform::GetTimeInSeconds();
	m_iFrames = 0;

	{
		Controls::WindowControl* pWindow = new Controls::WindowControl( this );
		pWindow->SetSize( 200, 200 );
		pWindow->SetPos( 600, 130 );
	}

	{
		Controls::WindowControl* pWindow = new Controls::WindowControl( this );
		pWindow->SetSize( 200, 200 );
		pWindow->SetPos( 500, 100 );
	}
}


void UnitTest::PrintText( const Gwen::UnicodeString& str )
{
	m_TextOutput->AddItem( str );
	m_TextOutput->ScrollToBottom();
}

void UnitTest::Render( Gwen::Skin::Base* skin )
{
	m_iFrames++;

	if ( m_fLastSecond < Gwen::Platform::GetTimeInSeconds() )
	{
		m_StatusBar->SetText( Gwen::Utility::Format( L"GWEN Unit Test - %i fps", m_iFrames*2 ) );

		m_fLastSecond = Gwen::Platform::GetTimeInSeconds() + 0.5f;
		m_iFrames = 0;
	}

	BaseClass::Render( skin );

}

void GUnit::UnitPrint( const Gwen::UnicodeString& str )
{
	m_pUnitTest->PrintText( str );
}

void GUnit::UnitPrint( const Gwen::String& str )
{
	UnitPrint( Utility::StringToUnicode( str ) );
}

