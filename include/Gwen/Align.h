/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include "Gwen/Controls/Base.h"

namespace Gwen 
{
	namespace Align
	{
		static void Center( Controls::Base* ctrl )
		{
			Controls::Base* parent = ctrl->GetParent(); 
			if ( !parent ) return;

			ctrl->SetPos( parent->GetPadding().left + (((parent->Width()-parent->GetPadding().left-parent->GetPadding().right) - ctrl->Width()) / 2), 
								(parent->Height() - ctrl->Height()) / 2 );
		}

		static void AlignLeft( Controls::Base* ctrl )
		{
			Controls::Base* parent = ctrl->GetParent(); 
			if ( !parent ) return;

			ctrl->SetPos( parent->GetPadding().left, ctrl->Y() );
		}

		static void CenterHorizontally( Controls::Base* ctrl )
		{
			Controls::Base* parent = ctrl->GetParent(); 
			if ( !parent ) return;


			ctrl->SetPos( parent->GetPadding().left + (((parent->Width()-parent->GetPadding().left-parent->GetPadding().right) - ctrl->Width()) / 2), ctrl->Y() );
		}

		static void AlignRight( Controls::Base* ctrl )
		{
			Controls::Base* parent = ctrl->GetParent(); 
			if ( !parent ) return;


			ctrl->SetPos( parent->Width() - ctrl->Width() - parent->GetPadding().right, ctrl->Y() );
		}

		static void AlignTop( Controls::Base* ctrl )
		{
			ctrl->SetPos( ctrl->X(), 0 );
		}

		static void CenterVertically( Controls::Base* ctrl )
		{
			Controls::Base* parent = ctrl->GetParent(); 
			if ( !parent ) return;

			ctrl->SetPos( ctrl->X(), (parent->Height() - ctrl->Height()) / 2 );
		}

		static void AlignBottom( Controls::Base* ctrl )
		{
			Controls::Base* parent = ctrl->GetParent(); 
			if ( !parent ) return;
	
			ctrl->SetPos( ctrl->X(), parent->Height() - ctrl->Height() );
		}

		static void PlaceBelow( Controls::Base* ctrl, Controls::Base* below, int iBorder = 0 )
		{
			ctrl->SetPos( ctrl->X(), below->Bottom() + iBorder );
		}

	}
}