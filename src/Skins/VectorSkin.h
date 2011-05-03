/*
	GWEN
	Copyright (c) 2009 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include "Gwen/Skin.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/Base.h"

class CVectorSkin : public Gwen::Skin::Base
{
	public:

		CVectorSkin()
		{
			m_BorderColor				= Gwen::Color( 80, 80, 80, 255 );
			m_BG						= Gwen::Color( 248, 248, 248, 255 );
			m_BGDark					= Gwen::Color( 235, 235, 235, 255 );

			m_colControl				= Gwen::Color( 240, 240, 240, 255 );
			m_colControlBright			= Gwen::Color( 255, 255, 255, 255 );
			m_colControlDark			= Gwen::Color( 214, 214, 214, 255 );
			m_colControlDarker			= Gwen::Color( 180, 180, 180, 255 );

			m_colControlOutlineNormal	= Gwen::Color( 112, 112, 112, 255 );
			m_colControlOutlineLight	= Gwen::Color( 144, 144, 144, 255 );
			m_colControlOutlineLighter	= Gwen::Color( 210, 210, 210, 255 );

			m_HighlightBG				= Gwen::Color( 192, 221, 252, 255 );
			m_HighlightBorder			= Gwen::Color(  51, 153, 255, 255 );


			m_ToolTipBackground			= Gwen::Color( 255, 255, 225, 255 );
			m_ToolTipBorder				= Gwen::Color( 0, 0, 0, 255 );

			m_DefaultFont.facename	= "Microsoft Sans Serif";
			m_DefaultFont.size		= 11;
		}


		virtual void DrawButton( Gwen::Controls::Base* control, bool bDepressed, bool bToggleState )
		{
			int w = control->Width();
			int h = control->Height();

			DrawButton( w, h, bToggleState || (bDepressed && control->IsHovered()), control->IsHovered() );

			Gwen::Render->SetDrawColor( Gwen::Color( 0, 0, 0, 255 ) );
		}

		virtual void DrawMenuItem( Gwen::Controls::Base* control, bool bSubmenuOpen )
		{
			if ( !bSubmenuOpen && !control->IsHovered() ) return;

			Gwen::Render->SetDrawColor( m_HighlightBG );
			Gwen::Render->DrawFilledRect( control->GetRenderBounds() );

			Gwen::Render->SetDrawColor( m_HighlightBorder );
			Gwen::Render->DrawLinedRect( control->GetRenderBounds() );

		}

		virtual void DrawMenuStrip( Gwen::Controls::Base* control )
		{
			int w = control->Width();
			int h = control->Height();

			Gwen::Render->SetDrawColor( Gwen::Color( 246, 248, 252, 255 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( 0, 0, w, h ) );

			Gwen::Render->SetDrawColor( Gwen::Color( 218, 224, 241, 150 ) );

			Gwen::Render->DrawFilledRect( Gwen::Rect( 0, h*0.4f, w, h*0.6f ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( 0, h*0.5f, w, h*0.5f ) );

		}

		virtual void DrawMenu( Gwen::Controls::Base* control, bool bPaddingDisabled )
		{
			int w = control->Width();
			int h = control->Height();

			Gwen::Render->SetDrawColor( m_colControlBright );
			Gwen::Render->DrawFilledRect( Gwen::Rect( 0, 0, w, h ) );

			if(!bPaddingDisabled)
			{
				Gwen::Render->SetDrawColor( m_colControl );
				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 0, 26, h ) );
			}

			Gwen::Render->SetDrawColor( m_colControlOutlineNormal );
			Gwen::Render->DrawLinedRect( Gwen::Rect( 0, 0, w, h ) );
		}

		virtual void DrawShadow( Gwen::Controls::Base* control )
		{
			int w = control->Width();
			int h = control->Height();

			int x = 4;
			int y = 6;

			Gwen::Render->SetDrawColor( Gwen::Color( 0, 0, 0, 10 ) );

			Gwen::Render->DrawFilledRect( Gwen::Rect( x, y, w, h ) );
			x+=2;
			Gwen::Render->DrawFilledRect( Gwen::Rect( x, y, w, h ) );
			y+=2;
			Gwen::Render->DrawFilledRect( Gwen::Rect( x, y, w, h ) );

		}

		virtual void DrawButton( int w, int h, bool bDepressed, bool bHovered )
		{
			if ( bDepressed )	Gwen::Render->SetDrawColor( m_colControlDark );
			else if ( bHovered )Gwen::Render->SetDrawColor( m_colControlBright );
			else				Gwen::Render->SetDrawColor( m_colControl );

			Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, w-2, h-2 ) );

			if ( bDepressed )	Gwen::Render->SetDrawColor( m_colControlDark );
			else if ( bHovered )Gwen::Render->SetDrawColor( m_colControl );
			else				Gwen::Render->SetDrawColor( m_colControlDark );

			Gwen::Render->DrawFilledRect( Gwen::Rect( 1, h*0.5, w-2, h*0.5-2 ) );

			if ( !bDepressed )
			{
				Gwen::Render->SetDrawColor( m_colControlBright );
				Gwen::Render->DrawShavedCornerRect( Gwen::Rect( 1, 1, w-2, h-2 ) );
			}
			else
			{
				Gwen::Render->SetDrawColor( m_colControlDarker );
				Gwen::Render->DrawShavedCornerRect( Gwen::Rect( 1, 1, w-2, h-2 ) );
			}

			// Border
			Gwen::Render->SetDrawColor( m_colControlOutlineNormal );
			Gwen::Render->DrawShavedCornerRect( Gwen::Rect( 0, 0, w, h ) );
		}

		virtual void DrawRadioButton( Gwen::Controls::Base* control, bool bSelected, bool bDepressed)
		{
			Gwen::Rect rect = control->GetRenderBounds();

			// Inside colour
			if ( control->IsHovered() )	Gwen::Render->SetDrawColor( Gwen::Color( 220, 242, 254, 255 ) );
			else Gwen::Render->SetDrawColor( m_colControlBright );

			Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );

			// Border
			if ( control->IsHovered() )	Gwen::Render->SetDrawColor( Gwen::Color( 85, 130, 164, 255 ) );
			else Gwen::Render->SetDrawColor( m_colControlOutlineLight );

			Gwen::Render->DrawShavedCornerRect( rect );

			Gwen::Render->SetDrawColor( Gwen::Color(   0,  50,  60, 15 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, rect.w-4, rect.h-4 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, rect.w*0.3f, rect.h-4 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, rect.w-4, rect.h*0.3f ) );

			if ( control->IsHovered() )	Gwen::Render->SetDrawColor( Gwen::Color( 121, 198, 249, 255 ) );
			else Gwen::Render->SetDrawColor( Gwen::Color( 0, 50, 60, 50 ) );

			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+3, 1, rect.h-5 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+3, rect.y+2, rect.w-5, 1 ) );
		}	

 
		virtual void DrawCheckBox( Gwen::Controls::Base* control, bool bSelected, bool bDepressed)
		{
			Gwen::Rect rect = control->GetRenderBounds();

			// Inside colour
			if ( control->IsHovered() )	Gwen::Render->SetDrawColor( Gwen::Color( 220, 242, 254, 255 ) );
			else Gwen::Render->SetDrawColor( m_colControlBright );

				Gwen::Render->DrawFilledRect( rect );

			// Border
			if ( control->IsHovered() )	Gwen::Render->SetDrawColor( Gwen::Color( 85, 130, 164, 255 ) );
			else Gwen::Render->SetDrawColor( m_colControlOutlineLight );

				Gwen::Render->DrawLinedRect( rect );

			Gwen::Render->SetDrawColor( Gwen::Color(   0,  50,  60, 15 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, rect.w-4, rect.h-4 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, rect.w*0.3f, rect.h-4 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, rect.w-4, rect.h*0.3f ) );

			if ( control->IsHovered() )	Gwen::Render->SetDrawColor( Gwen::Color( 121, 198, 249, 255 ) );
			else Gwen::Render->SetDrawColor( Gwen::Color( 0, 50, 60, 50 ) );

			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, 1, rect.h-4 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+2, rect.w-4, 1 ) );
		}

		virtual void DrawGroupBox( Gwen::Controls::Base* control, int textStart, int textHeight, int textWidth )
		{
			Gwen::Rect rect = control->GetRenderBounds();

			rect.y += textHeight * 0.5f;
			rect.h -= textHeight * 0.5f;

			Gwen::Color m_colDarker			= Gwen::Color(   0,  50,  60, 50 );
			Gwen::Color m_colLighter		= Gwen::Color( 255, 255, 255, 150 );

			Gwen::Render->SetDrawColor( m_colLighter );

				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1, textStart-3, 1 ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1+textStart+textWidth, rect.y+1, rect.w-textStart+textWidth-2, 1 ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.bottom()-1, rect.w-2, 1 ) );

				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1, 1, rect.h ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.right()-2, rect.y+1, 1, rect.h-1 ) );

			Gwen::Render->SetDrawColor( m_colDarker );

				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y, textStart-3, 1 ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1+textStart+textWidth, rect.y, rect.w-textStart-textWidth-2, 1 ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.bottom(), rect.w-2, 1 ) );
				
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x, rect.y+1, 1, rect.h-1 ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.right()-1, rect.y+1, 1, rect.h-1 ) );			
		}

		virtual void DrawTextBox( Gwen::Controls::Base* control, Gwen::Rect CursorRect )
		{
			Gwen::Rect rect = control->GetRenderBounds();

			Gwen::Render->SetDrawColor( m_colControlBright );
			Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );	

			// Only draw the cursor if we have keyboard focus
			if ( control->HasFocus() )
			{
				Gwen::Render->SetDrawColor( Gwen::Colors::Black );
				Gwen::Render->DrawFilledRect( CursorRect );		
			}

			Gwen::Render->SetDrawColor( m_colControlOutlineLight );

			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y, rect.w-2, 1 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x, rect.y+1, 1, rect.h-2 ) );

			Gwen::Render->SetDrawColor( m_colControlOutlineLighter );

			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.bottom()-1, rect.w-2, 1 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.right()-1, rect.y+1, 1, rect.h-2 ) );

			
		}

		virtual void DrawTabButton( Gwen::Controls::Base* control, bool bActive )
		{
			Gwen::Rect rect = control->GetRenderBounds();
			bool bHovered = control->IsHovered();

			if ( bActive )
			{
				Gwen::Render->SetDrawColor( m_colControl );
				Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1, rect.w-2, rect.h-1 ) );
			}
			else
			{
				if ( bHovered )Gwen::Render->SetDrawColor( m_colControlBright );
				else		   Gwen::Render->SetDrawColor( m_colControl );

				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-1 ) );

				if ( bHovered )Gwen::Render->SetDrawColor( m_colControl );
				else		   Gwen::Render->SetDrawColor( m_colControlDark );

				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, rect.h*0.5, rect.w-2, rect.h*0.5-1 ) );

				Gwen::Render->SetDrawColor( m_colControlBright );
				Gwen::Render->DrawShavedCornerRect( Gwen::Rect( 1, 1, rect.w-2, rect.h ) );
			}

			Gwen::Render->SetDrawColor( m_BorderColor );

			Gwen::Render->DrawShavedCornerRect( Gwen::Rect( 0, 0, rect.w, rect.h ) );
		}

		virtual void DrawTabControl( Gwen::Controls::Base* control, Gwen::Rect CurrentButtonRect )
		{
			Gwen::Rect rect = control->GetRenderBounds();

			Gwen::Render->SetDrawColor( m_colControl );
			Gwen::Render->DrawFilledRect( rect );	

			Gwen::Render->SetDrawColor( m_BorderColor );
			Gwen::Render->DrawLinedRect( rect );

			Gwen::Render->SetDrawColor( m_colControl );
			Gwen::Render->DrawFilledRect( CurrentButtonRect );
		}

		virtual void DrawWindow( Gwen::Controls::Base* control, int topHeight, bool inFocus )
		{
			Gwen::Rect rect = control->GetRenderBounds();

			// Titlebar
			if(inFocus)
				Gwen::Render->SetDrawColor( Gwen::Color( 87, 164, 232, 230 ) );
			else
				Gwen::Render->SetDrawColor( Gwen::Color( 87*0.70, 164*0.70, 232*0.70, 230 ) );

			int iBorderSize = 5;
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1, rect.w-2, topHeight-1 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+topHeight-1, iBorderSize, rect.h-2-topHeight ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+rect.w-iBorderSize, rect.y+topHeight-1, iBorderSize, rect.h-2-topHeight ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+rect.h-iBorderSize, rect.w-2, iBorderSize ) );

			//Gwen::Render->SetDrawColor( Gwen::Color( 0, 0, 0, 5 ) );
			//Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1+topHeight*0.5f, rect.w-2, topHeight*0.5f-1 ) );
			//Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1+topHeight*0.6f, rect.w-2, topHeight*0.4f-1 ) );
			//Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1+topHeight*0.7f, rect.w-2, topHeight*0.3f-1 ) );

			// Main inner
			Gwen::Render->SetDrawColor( Gwen::Color( m_colControlDark.r, m_colControlDark.g, m_colControlDark.b, 230 ) );
			Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+iBorderSize+1, rect.y+topHeight, rect.w-iBorderSize*2-2, rect.h-topHeight-iBorderSize-1 ) );

			// Light inner border
			Gwen::Render->SetDrawColor( Gwen::Color( 255, 255, 255, 100 ) );
			Gwen::Render->DrawShavedCornerRect( Gwen::Rect( rect.x+1, rect.y+1, rect.w-2, rect.h-2 ) );		

			//Gwen::Render->DrawLinedRect( Gwen::Rect( rect.x+4, rect.y+topHeight-2, rect.w - 8, rect.h - topHeight - 2 ) );
			//Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+topHeight+1, rect.w-4, 1 ) );
			//Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+2, rect.y+topHeight-1, rect.w-4, 1 ) );

			// Dark line between titlebar and main
			Gwen::Render->SetDrawColor( m_BorderColor );
			//Gwen::Render->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+topHeight-1, rect.w-2, 1 ) );

			// Inside border
			Gwen::Render->SetDrawColor( m_colControlOutlineNormal );
			Gwen::Render->DrawLinedRect( Gwen::Rect( rect.x+iBorderSize, rect.y+topHeight-1, rect.w - 10, rect.h - topHeight - (iBorderSize - 1) ) );

			// Dark outer border
			Gwen::Render->SetDrawColor( m_BorderColor );
			Gwen::Render->DrawShavedCornerRect( Gwen::Rect( rect.x, rect.y, rect.w, rect.h ) );		
		}

		virtual void DrawHighlight( Gwen::Controls::Base* control )
		{
			Gwen::Rect rect = control->GetRenderBounds();
			Gwen::Render->SetDrawColor( Gwen::Color( 255, 100, 255, 255 ) );
			Gwen::Render->DrawFilledRect( rect );
		}

		virtual void DrawScrollBar( Gwen::Controls::Base* control, bool isHorizontal, bool bDepressed )
		{
			Gwen::Rect rect = control->GetRenderBounds();
			if(bDepressed)
				Gwen::Render->SetDrawColor( m_colControlDarker );
			else
				Gwen::Render->SetDrawColor( m_colControlBright );
			Gwen::Render->DrawFilledRect( rect );
		}

		virtual void DrawTabTitleBar( Gwen::Controls::Base* control )
		{
			Gwen::Rect rect = control->GetRenderBounds();

			Gwen::Render->SetDrawColor( Gwen::Color( 177, 193, 214, 255 ) );
			Gwen::Render->DrawFilledRect( rect );

			Gwen::Render->SetDrawColor( m_BorderColor );
			rect.h += 1;
			Gwen::Render->DrawLinedRect( rect );
		}

		virtual void DrawProgressBar( Gwen::Controls::Base* control, bool isHorizontal, float progress)
		{
			Gwen::Rect rect = control->GetRenderBounds();
			Gwen::Color FillColour( 0, 211, 40, 255 );

			if( isHorizontal )
			{
				//Background
				Gwen::Render->SetDrawColor( m_colControlDark );
				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );
		
				//Right half
				Gwen::Render->SetDrawColor( FillColour );
				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w*progress-2, rect.h-2 ) );

				Gwen::Render->SetDrawColor( Gwen::Color( 255, 255, 255, 150 ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h*0.45f ) );
			}
			else
			{
				//Background 
				Gwen::Render->SetDrawColor( m_colControlDark );
				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );

				//Top half
				Gwen::Render->SetDrawColor( FillColour );
				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1 + (rect.h * (1 - progress)), rect.w-2, rect.h-2 ) );

				Gwen::Render->SetDrawColor( Gwen::Color( 255, 255, 255, 150 ) );
				Gwen::Render->DrawFilledRect( Gwen::Rect( 1, 1, rect.w*0.45f, rect.h-2 ) );
			}

			Gwen::Render->SetDrawColor( Gwen::Color( 255, 255, 255, 150 ) );
			Gwen::Render->DrawShavedCornerRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );

			Gwen::Render->SetDrawColor( Gwen::Color( 255, 255, 255, 70 ) );
			Gwen::Render->DrawShavedCornerRect( Gwen::Rect( 2, 2, rect.w-4, rect.h-4 ) );

			Gwen::Render->SetDrawColor( m_BorderColor );
			Gwen::Render->DrawShavedCornerRect( rect );	
		}
 
		virtual void DrawListBox( Gwen::Controls::Base* control )
		{
			Gwen::Rect rect = control->GetRenderBounds();

			Gwen::Render->SetDrawColor( m_colControlBright );
			Gwen::Render->DrawFilledRect( rect );

			Gwen::Render->SetDrawColor( m_BorderColor );
			Gwen::Render->DrawLinedRect( rect );
		}

		virtual void DrawListBoxLine( Gwen::Controls::Base* control, bool bSelected )
		{
			Gwen::Rect rect = control->GetRenderBounds();

			if ( bSelected )
			{
				Gwen::Render->SetDrawColor( m_HighlightBorder );
				Gwen::Render->DrawFilledRect( rect );
			}
			else if ( control->IsHovered() )
			{
				Gwen::Render->SetDrawColor( m_HighlightBG );
				Gwen::Render->DrawFilledRect( rect );
			}
		}
		
		
		virtual void DrawSlider( Gwen::Controls::Base* control, bool bIsHorizontal, int numNotches, int barSize)
		{
			Gwen::Rect rect = control->GetRenderBounds();
			Gwen::Rect notchRect = control->GetRenderBounds();

			//Draw notches
			if(numNotches >= 2 )
			{
				Gwen::Render->SetDrawColor( Gwen::Color( 80, 80, 80, 255 ) );

				if(bIsHorizontal)
				{
					notchRect.x += barSize * 0.5;
					notchRect.w -= barSize;

					for(int i = 0; i < numNotches; i++)
					{
						int add = ( (float)(notchRect.w / (float)( numNotches - 1 ) ) * i);
						Gwen::Render->DrawLine(notchRect.x + add, notchRect.y, notchRect.x + add, notchRect.y + notchRect.h * 0.5);
					}
				}
				else
				{
					notchRect.y += barSize * 0.5;
					notchRect.h -= barSize;

					for(int i = 0; i < numNotches; i++)
					{
						int add = ( (float)(notchRect.h / (float)( numNotches - 1 ) ) * i);
						Gwen::Render->DrawLine(notchRect.x, notchRect.y + add, notchRect.x + notchRect.w * 0.5, notchRect.y + add);
					}
				}

			}

			if(bIsHorizontal)
			{
				rect.y += rect.h * 0.4;
				rect.h -= rect.h * 0.8;
			}
			else
			{
				rect.x += rect.w * 0.4;
				rect.w -= rect.w * 0.8;
			}

			Gwen::Render->SetDrawColor( m_BGDark );
			Gwen::Render->DrawFilledRect( rect );

			Gwen::Render->SetDrawColor( m_colControlDarker );	
			Gwen::Render->DrawLinedRect( rect );
		}

		virtual void DrawComboBox( Gwen::Controls::Base* control )
		{
				Gwen::Rect rect = control->GetRenderBounds();

				Gwen::Render->SetDrawColor( m_colControlBright );
				Gwen::Render->DrawFilledRect( rect );

				Gwen::Render->SetDrawColor( m_BorderColor );
				Gwen::Render->DrawLinedRect( rect );

		}

		virtual void DrawKeyboardHighlight( Gwen::Controls::Base* control )
		{
				Gwen::Rect rect = control->GetRenderBounds();
				
				//draw the top and bottom
				bool skip = true;
				for(int i=0; i< rect.w*0.5; i++)
				{
					Gwen::Render->SetDrawColor( Gwen::Color( 0, 0, 0, 255 ) );
					if(!skip)
					{
						Gwen::Render->DrawPixel(rect.x + (i*2), rect.y);
						Gwen::Render->DrawPixel(rect.x + (i*2), rect.y+rect.h-1);
					}
					else
						skip = !skip;
				}
				skip = false;
				for(int i=0; i< rect.h*0.5; i++)
				{
					Gwen::Render->SetDrawColor( Gwen::Color( 0, 0, 0, 255 ) );
					if(!skip)
					{
						Gwen::Render->DrawPixel(rect.x , rect.y +i*2);
						Gwen::Render->DrawPixel(rect.x +rect.w-1, rect.y +i*2 );
					}
					else
						skip = !skip;
				}
		}	

		virtual void DrawToolTip( Gwen::Rect rct )
		{
				rct.x -= 3;
				rct.y -= 3;
				rct.w += 6;
				rct.h += 6;

				Gwen::Render->SetDrawColor( m_ToolTipBackground );
				Gwen::Render->DrawFilledRect( rct );

				Gwen::Render->SetDrawColor( m_ToolTipBorder );
				Gwen::Render->DrawLinedRect( rct );
		}

		Gwen::Color m_BorderColor, m_colControlOutlineLight, m_colControlOutlineLighter;
		Gwen::Color m_BG, m_BGDark;
		Gwen::Color m_colControl, m_colControlBorderHighlight, m_colControlDarker, m_colControlOutlineNormal, m_colControlBright, m_colControlDark;

		Gwen::Color m_HighlightBG, m_HighlightBorder;

		Gwen::Color m_ToolTipBackground, m_ToolTipBorder;
}; 