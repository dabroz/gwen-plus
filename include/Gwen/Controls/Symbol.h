/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include "Base.h"
#include "Gwen/BaseRender.h"
#include "Gwen/Skin.h"

namespace Gwen 
{
	namespace Controls
	{

		namespace Symbol 
		{
			class GWEN_EXPORT Base : public Controls::Base
			{
				public:

					GWEN_CONTROL_INLINE( Base, Controls::Base )
					{
						SetMouseInputEnabled( false );
					}

			};

			class GWEN_EXPORT Arrow : public Base
			{
				public:

					Arrow( Gwen::Controls::Base* pnl ) : Base( pnl )
					{
					}

					virtual void Render( Gwen::Skin::Base* pSkin )
					{
						Rect r( Width() / 2 - 2, Height() / 2 - 2, 5, 5 );
						pSkin->DrawArrowRight( r );
					}

			};

		}
	}

}
