/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include "Base.h"
#include "Gwen/BaseRender.h"
#include "Gwen/Font.h"

namespace Gwen 
{
	namespace Controls
	{

		// http://www.vbaccelerator.com/home/VB/Code/Libraries/Subclassing/Reliable_Interception_of_WM_NCHITTEST/marlett.gif

		namespace Symbol 
		{
			class GWEN_EXPORT Base : public Controls::Label
			{
				public:

					GWEN_CONTROL_INLINE( Base, Controls::Label )
					{
						m_Font.facename = L"Marlett";
						m_Font.size = 10.0f;

						SetFont( &m_Font );
						SetText( "8" );
						SetAlignment( Pos::Center );

						SetMouseInputEnabled( false );
					}

					virtual ~Base()
					{
						GetSkin()->ReleaseFont( &m_Font );
					}
					virtual void SetFontSize( float size ) { m_Font.size = size; }

				private:

					Gwen::Font	m_Font;

			};

			class GWEN_EXPORT Arrow : public Base
			{
				public:

					Arrow( Gwen::Controls::Base* pnl ) : Base( pnl )
					{

						SetText( "8" );
					}

			};

			class GWEN_EXPORT Check : public Base
			{
				public:

					Check( Gwen::Controls::Base* pnl ) : Base( pnl )
					{
						SetFontSize( 15.0f );
						SetText( "a" );
					}
			};

			class GWEN_EXPORT Dot : public Base
			{
				public:

					Dot( Gwen::Controls::Base* pnl ) : Base( pnl )
					{
						SetFontSize( 15.0f );
						SetText( "8" );
					}
			};
		}
	}

}
