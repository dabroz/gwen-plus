/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/Highlight.h"
#include "Gwen/DragAndDrop.h"
#include "Gwen/Controls/WindowControl.h"

using namespace Gwen;
using namespace Gwen::Controls;

class TabControlInner : public Base
{
	public:

		GWEN_CONTROL_INLINE( TabControlInner, Base )
		{
			m_ButtonRect = Rect( 0, 0, 0, 0 );
		}

		void Render( Skin::Base* skin )
		{
			skin->DrawTabControl( this, m_ButtonRect );
		}

		void UpdateCurrentButton( Rect rct )
		{
			m_ButtonRect = rct;
		}

		Rect m_ButtonRect;
};

GWEN_CONTROL_CONSTRUCTOR( TabControl )
{
	m_pCurrentButton = NULL;

	m_TabStrip = new TabStrip( this );
	m_TabStrip->Dock( Pos::Top );
	m_TabStrip->SetWidth( 100 );
	m_TabStrip->SetHeight( 20 );

	m_InnerPanel = new TabControlInner( this );
	m_InnerPanel->Dock( Pos::Fill );


	SetTabable( false );
}



TabButton* TabControl::AddPage( const UnicodeString& strText, Controls::Base* pPage )
{
	if ( !pPage )
	{
		pPage = new Base( this );
	}
	else
	{
		pPage->SetParent( this );
	}

	TabButton* pButton = new TabButton( m_TabStrip );
		pButton->SetText( strText );
		pButton->SetPage( pPage );
		pButton->SetTabable( false );

	AddPage( pButton );
	return pButton;
}

void TabControl::AddPage( TabButton* pButton )
{
	Base* pPage = pButton->GetPage();
		pPage->SetParent( this );
		pPage->SetHidden( true );
		pPage->SetMargin( Margin( 6, 6, 6, 6 ) );
		pPage->Dock( Pos::Fill );

	pButton->SetParent( m_TabStrip );
	pButton->Dock( Pos::Left );
	pButton->SizeToContents();
	if ( pButton->GetTabControl() ) pButton->onPress.RemoveHandler( pButton->GetTabControl() );
	pButton->SetTabControl( this );
	pButton->onPress.Add( this, &TabControl::OnTabPressed );



	if ( !m_pCurrentButton )
	{
		pButton->OnPress();
	}

	onAddTab.Call( this );

	Invalidate();
}

void TabControl::OnTabPressed( Controls::Base* control )
{
	TabButton* pButton = dynamic_cast<TabButton*>(control);
	if ( !pButton ) return;

	Base* pPage = pButton->GetPage();
	if ( !pPage ) return;

	if ( m_pCurrentButton == pButton)
		return;

	if ( m_pCurrentButton )
	{
		Base* pPage = m_pCurrentButton->GetPage();
		if ( pPage )
		{
			pPage->SetHidden( true );
		}
		m_pCurrentButton = NULL;
	}

	m_pCurrentButton = pButton;

	pPage->SetHidden( false );
	
	m_TabStrip->Invalidate();
	Invalidate();	
}

void TabControl::PostLayout( Skin::Base* skin )
{
	BaseClass::PostLayout( skin );

	if ( m_TabStrip->Hidden() )
	{
		dynamic_cast<TabControlInner*>(m_InnerPanel)->UpdateCurrentButton( Rect( 0, 0, 0, 0 ) );
	}
	else if ( m_pCurrentButton )
	{
		Rect rct;

		Point p = m_pCurrentButton->LocalPosToCanvas( Point( 0, 0 ) );
		p = m_InnerPanel->CanvasPosToLocal( p );

		rct = Rect( p.x+1, p.y+1, m_pCurrentButton->Width()-2, m_pCurrentButton->Height()-2 );
		dynamic_cast<TabControlInner*>(m_InnerPanel)->UpdateCurrentButton( rct );
	}
	
}

void TabControl::OnLoseTab( TabButton* pButton )
{
	if ( m_pCurrentButton == pButton )
		m_pCurrentButton = NULL;

	//TODO: Select a tab if any exist.

	onLoseTab.Call( this );

	Invalidate();	
}

int TabControl::TabCount( void )
{
	return m_TabStrip->NumChildren();
}

void TabControl::SetTabStripPosition( int iDock )
{
	m_TabStrip->SetTabPosition( iDock );
}

bool TabControl::DoesAllowDrag()
{
	return m_TabStrip->AllowsTabReorder();
}
