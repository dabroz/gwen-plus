/*
	GWEN
	Copyright (c) 2009 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include "Base.h"
#include "Gwen/BaseRender.h"

namespace Gwen 
{
	namespace Controls
	{
		/*

		TODO!

		*/

		class ToolBarStrip : public Base
		{
			GWEN_CONTROL_INLINE( ToolBarStrip, Base )
			{
				SetPadding( Padding( 2, 2, 2, 2 ) );
			}

			virtual void Render( Skin::Base* skin )
			{
				skin->DrawMenuStrip( this );
			}

			virtual void RenderUnder( Skin::Base* skin )
			{

			}

			virtual void Layout( Skin::Base* skin )
			{

			}

		};
	}

}
