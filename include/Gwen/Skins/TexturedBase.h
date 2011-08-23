#pragma once
#ifndef GWEN_SKINS_TEXTUREDBASE_H
#define GWEN_SKINS_TEXTUREDBASE_H

#include "Gwen/Skin.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/Base.h"
#include "Gwen/Texture.h"
#include "Gwen/Skins/Texturing.h"

namespace Gwen 
{
	namespace Skin
	{
		class TexturedBase : public Gwen::Skin::Base
		{
			public:

				Gwen::Color m_colBorderColor;
				Gwen::Color m_colBG; 
				Gwen::Color m_colBGDark;
				Gwen::Color m_colControlDarker;
				Gwen::Color m_colControlBright;
				Gwen::Color m_colControlDark;
				Gwen::Color m_colHighlightBG;
				Gwen::Color m_colHighlightBorder;
				Gwen::Color m_colToolTipBackground;
				Gwen::Color m_colToolTipBorder;
				Gwen::Color m_colModal;

				Texture m_Texture;

				Texturing::Bordered	m_texButton;
				Texturing::Bordered	m_texButton_Hovered;
				Texturing::Bordered	m_texButton_Dead;
				Texturing::Bordered	m_texButton_Pressed;

				Texturing::Bordered	m_texMenu_Strip, m_texMenuBG, m_texMenuBG_Margin;
				Texturing::Bordered	m_texMenuBG_Hover, m_texMenuBG_Spacer;
				Texturing::Bordered	m_texShadow;

				Texturing::Bordered	m_texTextBox, m_texTextBox_Focus, m_texTextBox_Disabled;

				Texturing::Bordered	m_texTab_Control, m_texTabBar;

				Texturing::Bordered m_texTabB_Active, m_texTabB_Inactive;
				Texturing::Bordered m_texTabT_Active, m_texTabT_Inactive;
				Texturing::Bordered m_texTabL_Active, m_texTabL_Inactive;
				Texturing::Bordered m_texTabR_Active, m_texTabR_Inactive;

				Texturing::Bordered	m_texWindow, m_texWindow_Inactive;
				Texturing::Bordered	m_texTreeBG;

				Texturing::Single	m_Checkbox, m_Checkbox_Checked;
				Texturing::Single	m_CheckboxD, m_CheckboxD_Checked;
				Texturing::Single	m_RadioButton, m_RadioButton_Checked;
				Texturing::Single	m_RadioButtonD, m_RadioButtonD_Checked;

				Texturing::Single m_CheckMark;

			
				Texturing::Single m_TreeMinus, m_TreePlus;

				struct
				{
					struct 
					{
						Texturing::Single Close;
						Texturing::Single Close_Hover;
						Texturing::Single Close_Down;
						Texturing::Single Close_Disabled;

					} Window;

				} Textures;

				
				virtual void Init( const TextObject& TextureName )
				{
					m_colBorderColor			= Gwen::Color( 80, 80, 80, 255 );
					m_colBG						= Gwen::Color( 248, 248, 248, 255 );
					m_colBGDark					= Gwen::Color( 235, 235, 235, 255 );

					m_colControlBright			= Gwen::Color( 255, 255, 255, 255 );
					m_colControlDark			= Gwen::Color( 214, 214, 214, 255 );
					m_colControlDarker			= Gwen::Color( 180, 180, 180, 255 );

					m_colHighlightBG			= Gwen::Color( 192, 221, 252, 255 );
					m_colHighlightBorder		= Gwen::Color(  51, 153, 255, 255 );

					m_colToolTipBackground		= Gwen::Color( 255, 255, 225, 255 );
					m_colToolTipBorder			= Gwen::Color( 0, 0, 0, 255 );

					m_colModal = Gwen::Color( 25, 25, 25, 150 );

					m_DefaultFont.facename	= L"Microsoft Sans Serif";
					m_DefaultFont.size		= 11;

					m_Texture.Load( TextureName, GetRender() );

					Colors.Window.TitleActive	= GetRender()->PixelColour( &m_Texture, 4, 508, Color( 255, 0, 0 ) );
					Colors.Window.TitleInactive	= GetRender()->PixelColour( &m_Texture, 12, 508, Color( 255, 255, 0) );

					m_texWindow.Init			( &m_Texture, 0, 0, 127,		127,	Margin( 8, 32, 8, 8 ) );
					m_texWindow_Inactive.Init	( &m_Texture, 128, 0, 127,		127,	Margin( 8, 32, 8, 8 ) );
					m_texButton.Init			( &m_Texture, 480, 0,	31,		31,		Margin( 8, 8, 8, 8 ) );
					m_texButton_Hovered.Init	( &m_Texture, 480, 32,	31,		31,		Margin( 8, 8, 8, 8 ) );
					m_texButton_Dead.Init		( &m_Texture, 480, 64,	31,		31,		Margin( 8, 8, 8, 8 ) );
					m_texButton_Pressed.Init	( &m_Texture, 480, 96,	31,		31,		Margin( 8, 8, 8, 8 ) );
					m_texShadow.Init			( &m_Texture, 448, 0,	31,		31,		Margin( 8, 8, 8, 8 ) );
					m_texTreeBG.Init			( &m_Texture, 256, 128, 127,	127,	Margin( 16, 16, 16, 16 ) );
					m_Checkbox_Checked.Init			( &m_Texture, 448, 32, 15, 15 );
					m_Checkbox.Init					( &m_Texture, 464, 32, 15, 15 );
					m_CheckboxD_Checked.Init		( &m_Texture, 448, 48, 15, 15 );
					m_CheckboxD.Init				( &m_Texture, 464, 48, 15, 15 );
					m_RadioButton_Checked.Init		( &m_Texture, 448, 64, 15, 15 );
					m_RadioButton.Init				( &m_Texture, 464, 64, 15, 15 );
					m_RadioButtonD_Checked.Init		( &m_Texture, 448, 80, 15, 15 );
					m_RadioButtonD.Init				( &m_Texture, 464, 80, 15, 15 );
					m_TreePlus.Init					( &m_Texture, 448, 96, 15, 15 );
					m_TreeMinus.Init				( &m_Texture, 464, 96, 15, 15 );
					m_texMenu_Strip.Init			( &m_Texture, 0, 128, 127, 21, Margin( 1, 1, 1, 1 ) );
					m_texTextBox.Init				( &m_Texture, 0, 150, 127, 21, Margin( 4, 4, 4, 4 ) );
					m_texTextBox_Focus.Init			( &m_Texture, 0, 172, 127, 21, Margin( 4, 4, 4, 4 ) );
					m_texTextBox_Disabled.Init		( &m_Texture, 0, 193, 127, 21, Margin( 4, 4, 4, 4 ) );
					m_texMenuBG_Margin.Init			( &m_Texture, 128, 128, 127, 63, Margin( 24, 8, 8, 8 ) );
					m_texMenuBG.Init				( &m_Texture, 128, 192, 127, 63, Margin( 8, 8, 8, 8 ) );
					m_texMenuBG_Hover.Init			( &m_Texture, 128, 256, 127, 31, Margin( 8, 8, 8, 8 ) );
					m_texMenuBG_Spacer.Init			( &m_Texture, 128, 288, 127, 3, Margin( 8, 8, 8, 8 ) );	// TODO!
					m_texTab_Control.Init			( &m_Texture, 0, 256, 127, 127, Margin( 8, 8, 8, 8 ) );
					m_texTabB_Active.Init			( &m_Texture, 0,		416, 63, 31, Margin( 8, 8, 8, 8 ) );
					m_texTabB_Inactive.Init			( &m_Texture, 0+128,	416, 63, 31, Margin( 8, 8, 8, 8 ) );
					m_texTabT_Active.Init			( &m_Texture, 0,		384, 63, 31, Margin( 8, 8, 8, 8 ) );
					m_texTabT_Inactive.Init			( &m_Texture, 0+128,	384, 63, 31, Margin( 8, 8, 8, 8 ) );
					m_texTabL_Active.Init			( &m_Texture, 64,		384, 31, 63, Margin( 8, 8, 8, 8 ) );
					m_texTabL_Inactive.Init			( &m_Texture, 64+128,	384, 31, 63, Margin( 8, 8, 8, 8 ) );
					m_texTabR_Active.Init			( &m_Texture, 96,		384, 31, 63, Margin( 8, 8, 8, 8 ) );
					m_texTabR_Inactive.Init			( &m_Texture, 96+128,	384, 31, 63, Margin( 8, 8, 8, 8 ) );
					m_texTabBar.Init				( &m_Texture, 128, 352, 127, 31, Margin( 4, 4, 4, 4 ) );

					Textures.Window.Close.Init			( &m_Texture, 0, 224, 24, 24 );
					Textures.Window.Close_Hover.Init	( &m_Texture, 32, 224, 24, 24 );
					Textures.Window.Close_Down.Init		( &m_Texture, 64, 224, 24, 24 );
					Textures.Window.Close_Disabled.Init	( &m_Texture, 96, 224, 24, 24 );

				}


				virtual void DrawButton( Gwen::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled )
				{
					// Todo: Depressed AND hovered?

					if ( bDepressed )
						m_texButton_Pressed.Draw( GetRender(), control->GetRenderBounds() );
					else if ( bHovered )
						m_texButton_Hovered.Draw( GetRender(), control->GetRenderBounds() );
					else
						m_texButton.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawMenuItem( Gwen::Controls::Base* control, bool bSubmenuOpen, bool bChecked  )
				{
					if ( bSubmenuOpen || control->IsHovered() )
						m_texMenuBG_Hover.Draw( GetRender(), control->GetRenderBounds() );

					if ( bChecked )
						m_CheckMark.Draw( GetRender(), Gwen::Rect( control->GetRenderBounds().x+2, control->GetRenderBounds().y+2, 16, 16 ));
				}

				virtual void DrawMenuStrip( Gwen::Controls::Base* control )
				{
					m_texMenu_Strip.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawMenu( Gwen::Controls::Base* control, bool bPaddingDisabled )
				{
					if ( !bPaddingDisabled )
					{
						return m_texMenuBG_Margin.Draw( GetRender(), control->GetRenderBounds() );
					}

					m_texMenuBG.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawShadow( Gwen::Controls::Base* control )
				{
					Gwen::Rect r = control->GetRenderBounds();
					r.x -= 4;
					r.y -= 4;
					r.w += 10;
					r.h += 10;

					m_texShadow.Draw( GetRender(), r );
				}

				virtual void DrawRadioButton( Gwen::Controls::Base* control, bool bSelected, bool bDepressed)
				{
					if ( bSelected )
					{
						if ( control->IsDisabled() )
							m_RadioButtonD_Checked.Draw( GetRender(), control->GetRenderBounds() );
						else
							m_RadioButton_Checked.Draw( GetRender(), control->GetRenderBounds() );
					}
					else
					{
						if ( control->IsDisabled() )
							m_RadioButtonD.Draw( GetRender(), control->GetRenderBounds() );
						else
							m_RadioButton.Draw( GetRender(), control->GetRenderBounds() );						
					}
				}	

		 
				virtual void DrawCheckBox( Gwen::Controls::Base* control, bool bSelected, bool bDepressed)
				{
					if ( bSelected )
					{
						if ( control->IsDisabled() )
							m_CheckboxD_Checked.Draw( GetRender(), control->GetRenderBounds() );
						else
							m_Checkbox_Checked.Draw( GetRender(), control->GetRenderBounds() );
					}
					else
					{
						if ( control->IsDisabled() )
							m_CheckboxD.Draw( GetRender(), control->GetRenderBounds() );
						else
							m_Checkbox.Draw( GetRender(), control->GetRenderBounds() );						
					}
				}

				virtual void DrawGroupBox( Gwen::Controls::Base* control, int textStart, int textHeight, int textWidth )
				{
					Gwen::Rect rect = control->GetRenderBounds();

					rect.y += textHeight * 0.5f;
					rect.h -= textHeight * 0.5f;

					Gwen::Color m_colDarker			= Gwen::Color(   0,  50,  60, 50 );
					Gwen::Color m_colLighter		= Gwen::Color( 255, 255, 255, 150 );

					GetRender()->SetDrawColor( m_colLighter );

						GetRender()->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1, textStart-3, 1 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( rect.x+1+textStart+textWidth, rect.y+1, rect.w-textStart+textWidth-2, 1 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( rect.x+1, (rect.y + rect.h)-1, rect.x+rect.w-2, 1 ) );

						GetRender()->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y+1, 1, rect.h ) );
						GetRender()->DrawFilledRect( Gwen::Rect( (rect.x + rect.w)-2, rect.y+1, 1, rect.h-1 ) );

					GetRender()->SetDrawColor( m_colDarker );

						GetRender()->DrawFilledRect( Gwen::Rect( rect.x+1, rect.y, textStart-3, 1 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( rect.x+1+textStart+textWidth, rect.y, rect.w-textStart-textWidth-2, 1 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( rect.x+1, (rect.y + rect.h)-1, rect.x+rect.w-2, 1 ) );
						
						GetRender()->DrawFilledRect( Gwen::Rect( rect.x, rect.y+1, 1, rect.h-1 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( (rect.x + rect.w)-1, rect.y+1, 1, rect.h-1 ) );			
				}

				virtual void DrawTextBox( Gwen::Controls::Base* control )
				{
					if ( control->IsDisabled() )
						return m_texTextBox_Disabled.Draw( GetRender(), control->GetRenderBounds() );

					if ( control->HasFocus() )
						m_texTextBox_Focus.Draw( GetRender(), control->GetRenderBounds() );
					else
						m_texTextBox.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawActiveTabButton( Gwen::Controls::Base* control, int dir )
				{
					GetRender()->EndClip();

					if ( dir == Pos::Bottom )	return m_texTabB_Active.Draw( GetRender(), control->GetRenderBounds() + Rect( 0, -8, 0, 8 ) );
					if ( dir == Pos::Top )		return m_texTabT_Active.Draw( GetRender(), control->GetRenderBounds() + Rect( 0, 0, 0, 8 ) );
					if ( dir == Pos::Left )		return m_texTabL_Active.Draw( GetRender(), control->GetRenderBounds() + Rect( 0, 0, 8, 0 ) );
					if ( dir == Pos::Right )	return m_texTabR_Active.Draw( GetRender(), control->GetRenderBounds() + Rect( -8, 0, 8, 0 ) );

					GetRender()->StartClip();
				}

				virtual void DrawTabButton( Gwen::Controls::Base* control, bool bActive, int dir )
				{
					if ( bActive )
						return DrawActiveTabButton( control, dir );
				
					if ( dir == Pos::Bottom )	return m_texTabB_Inactive.Draw( GetRender(), control->GetRenderBounds() );
					if ( dir == Pos::Top )		return m_texTabT_Inactive.Draw( GetRender(), control->GetRenderBounds() );
					if ( dir == Pos::Left )		return m_texTabL_Inactive.Draw( GetRender(), control->GetRenderBounds() );
					if ( dir == Pos::Right )	return m_texTabR_Inactive.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawTabControl( Gwen::Controls::Base* control )
				{
					m_texTab_Control.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawTabTitleBar( Gwen::Controls::Base* control )
				{
					m_texTabBar.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawWindow( Gwen::Controls::Base* control, int topHeight, bool inFocus )
				{
					Gwen::Rect rect = control->GetRenderBounds();

					if ( inFocus ) m_texWindow.Draw( GetRender(), control->GetRenderBounds() );
					else m_texWindow_Inactive.Draw( GetRender(), control->GetRenderBounds() );	
				}

				virtual void DrawHighlight( Gwen::Controls::Base* control )
				{
					Gwen::Rect rect = control->GetRenderBounds();
					GetRender()->SetDrawColor( Gwen::Color( 255, 100, 255, 255 ) );
					GetRender()->DrawFilledRect( rect );
				}

				virtual void DrawScrollBar( Gwen::Controls::Base* control, bool isHorizontal, bool bDepressed )
				{
					Gwen::Rect rect = control->GetRenderBounds();
					if (bDepressed)
						GetRender()->SetDrawColor( m_colControlDarker );
					else
						GetRender()->SetDrawColor( m_colControlBright );
					GetRender()->DrawFilledRect( rect );
				}

				virtual void DrawScrollBarBar( Controls::Base* control, bool bDepressed, bool isHovered, bool isHorizontal  )
				{
					//TODO: something specialized
					DrawButton( control, bDepressed, isHovered, false );
				}



				virtual void DrawProgressBar( Gwen::Controls::Base* control, bool isHorizontal, float progress)
				{
					Gwen::Rect rect = control->GetRenderBounds();
					Gwen::Color FillColour( 0, 211, 40, 255 );

					if ( isHorizontal )
					{
						//Background
						GetRender()->SetDrawColor( m_colControlDark );
						GetRender()->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );
				
						//Right half
						GetRender()->SetDrawColor( FillColour );
						GetRender()->DrawFilledRect( Gwen::Rect( 1, 1, rect.w*progress-2, rect.h-2 ) );

						GetRender()->SetDrawColor( Gwen::Color( 255, 255, 255, 150 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h*0.45f ) );
					}
					else
					{
						//Background 
						GetRender()->SetDrawColor( m_colControlDark );
						GetRender()->DrawFilledRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );

						//Top half
						GetRender()->SetDrawColor( FillColour );
						GetRender()->DrawFilledRect( Gwen::Rect( 1, 1 + (rect.h * (1 - progress)), rect.w-2, rect.h * progress - 2 ) );

						GetRender()->SetDrawColor( Gwen::Color( 255, 255, 255, 150 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( 1, 1, rect.w*0.45f, rect.h-2 ) );
					}

					GetRender()->SetDrawColor( Gwen::Color( 255, 255, 255, 150 ) );
					GetRender()->DrawShavedCornerRect( Gwen::Rect( 1, 1, rect.w-2, rect.h-2 ) );

					GetRender()->SetDrawColor( Gwen::Color( 255, 255, 255, 70 ) );
					GetRender()->DrawShavedCornerRect( Gwen::Rect( 2, 2, rect.w-4, rect.h-4 ) );

					GetRender()->SetDrawColor( m_colBorderColor );
					GetRender()->DrawShavedCornerRect( rect );	
				}
		 
				virtual void DrawListBox( Gwen::Controls::Base* control )
				{
					Gwen::Rect rect = control->GetRenderBounds();

					GetRender()->SetDrawColor( m_colControlBright );
					GetRender()->DrawFilledRect( rect );

					GetRender()->SetDrawColor( m_colBorderColor );
					GetRender()->DrawLinedRect( rect );
				}

				virtual void DrawListBoxLine( Gwen::Controls::Base* control, bool bSelected )
				{
					Gwen::Rect rect = control->GetRenderBounds();

					if ( bSelected )
					{
						GetRender()->SetDrawColor( m_colHighlightBorder );
						GetRender()->DrawFilledRect( rect );
					}
					else if ( control->IsHovered() )
					{
						GetRender()->SetDrawColor( m_colHighlightBG );
						GetRender()->DrawFilledRect( rect );
					}
				}
				
				
				virtual void DrawSlider( Gwen::Controls::Base* control, bool bIsHorizontal, int numNotches, int barSize)
				{
					Gwen::Rect rect = control->GetRenderBounds();
					Gwen::Rect notchRect = rect;

					if ( bIsHorizontal )
					{
						rect.y += rect.h * 0.4;
						rect.h -= rect.h * 0.8;
					}
					else
					{
						rect.x += rect.w * 0.4;
						rect.w -= rect.w * 0.8;
					}

					GetRender()->SetDrawColor( m_colBGDark );
					GetRender()->DrawFilledRect( rect );

					GetRender()->SetDrawColor( m_colControlDarker );	
					GetRender()->DrawLinedRect( rect );
				}

				virtual void DrawComboBox( Gwen::Controls::Base* control )
				{
					DrawTextBox( control );
				}

				virtual void DrawKeyboardHighlight( Gwen::Controls::Base* control, const Gwen::Rect& r, int iOffset )
				{
						Gwen::Rect rect = r;
		  
						rect.x += iOffset;
						rect.y += iOffset;
						rect.w -= iOffset*2;
						rect.h -= iOffset*2;
						
						//draw the top and bottom
						bool skip = true;
						for(int i=0; i< rect.w*0.5; i++)
						{
							m_Render->SetDrawColor( Gwen::Color( 0, 0, 0, 255 ) );
							if (!skip)
							{
								GetRender()->DrawPixel(rect.x + (i*2), rect.y);
								GetRender()->DrawPixel(rect.x + (i*2), rect.y+rect.h-1);
							}
							else
								skip = !skip;
						}
						skip = false;
						for(int i=0; i< rect.h*0.5; i++)
						{
							GetRender()->SetDrawColor( Gwen::Color( 0, 0, 0, 255 ) );
							if (!skip)
							{
								GetRender()->DrawPixel(rect.x , rect.y +i*2);
								GetRender()->DrawPixel(rect.x +rect.w-1, rect.y +i*2 );
							}
							else
								skip = !skip;
						}
				}	

				virtual void DrawToolTip( Gwen::Controls::Base* control )
				{
					Gwen::Rect rct = control->GetRenderBounds();
						rct.x -= 3;
						rct.y -= 3;
						rct.w += 6;
						rct.h += 6;

						GetRender()->SetDrawColor( m_colToolTipBackground );
						GetRender()->DrawFilledRect( rct );

						GetRender()->SetDrawColor( m_colToolTipBorder );
						GetRender()->DrawLinedRect( rct );
				}

				virtual void DrawScrollButton( Gwen::Controls::Base* control, int iDirection, bool bDepressed )
				{
					DrawButton( control, bDepressed, false, false );

					m_Render->SetDrawColor( Gwen::Color( 0, 0, 0, 240 ) );

					Gwen::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );

					if ( iDirection == Gwen::Pos::Top ) DrawArrowUp( r );
					else if ( iDirection == Gwen::Pos::Bottom ) DrawArrowDown( r );
					else if ( iDirection == Gwen::Pos::Left ) DrawArrowLeft( r );
					else DrawArrowRight( r );
				}

				virtual void DrawComboBoxButton( Gwen::Controls::Base* control, bool bDepressed )
				{	
					m_Render->SetDrawColor( Gwen::Color( 0, 0, 0, 240 ) );

					Gwen::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );
					DrawArrowDown( r );
				}

				virtual void DrawNumericUpDownButton( Gwen::Controls::Base* control, bool bDepressed, bool bUp )
				{
				//	DrawButton( control->Width(), control->Height(), bDepressed, false, true );

					m_Render->SetDrawColor( Gwen::Color( 0, 0, 0, 240 ) );

					Gwen::Rect r( control->Width() / 2 - 2, control->Height() / 2 - 2, 5, 5 );

					if ( bUp ) DrawArrowUp( r );
					else DrawArrowDown( r );
				}

				virtual void DrawStatusBar( Controls::Base* control )
				{
					DrawBackground( control );
				}


				virtual void DrawBackground( Gwen::Controls::Base* control )
				{
					Gwen::Rect rect = control->GetRenderBounds();
					m_Render->SetDrawColor( m_colBGDark );
					m_Render->DrawFilledRect( rect );
					m_Render->SetDrawColor( m_colControlDarker);
					m_Render->DrawLinedRect( rect );
				}

				virtual void DrawTreeButton( Controls::Base* control, bool bOpen )
				{
					Gwen::Rect rect = control->GetRenderBounds();

					if ( bOpen )
						m_TreeMinus.Draw( GetRender(), rect );
					else
						m_TreePlus.Draw( GetRender(), rect );
				}

				virtual void DrawPropertyRow( Controls::Base* control, int iWidth, bool bBeingEdited )
				{
					
					Gwen::Rect rect = control->GetRenderBounds();


					if ( bBeingEdited )
					{
						GetRender()->SetDrawColor( m_colHighlightBG );
						GetRender()->DrawFilledRect( Gwen::Rect( 0, rect.y, iWidth, rect.h ) );
					}

					//GetRender()->SetDrawColor( m_colControlOutlineLighter );

					GetRender()->DrawFilledRect( Gwen::Rect( iWidth, rect.y, 1, rect.h ) );

					rect.y += rect.h-1;
					rect.h = 1;


					GetRender()->DrawFilledRect( rect );
					
				}

				virtual void DrawPropertyTreeNode( Controls::Base* control, int BorderLeft, int BorderTop )
				{
					
					Gwen::Rect rect = control->GetRenderBounds();

					//GetRender()->SetDrawColor( m_colControlOutlineLighter );

					GetRender()->DrawFilledRect( Gwen::Rect( rect.x, rect.y, BorderLeft, rect.h ) );
					GetRender()->DrawFilledRect( Gwen::Rect( rect.x + BorderLeft, rect.y, rect.w - BorderLeft, BorderTop ) );
					
				}

				void DrawTreeNode( Controls::Base* ctrl, bool bOpen, bool bSelected, int iLabelHeight, int iLabelWidth, int iHalfWay, int iLastBranch, bool bIsRoot )
				{
					if ( bSelected )
					{
						GetRender()->SetDrawColor( Color( 0, 150, 255, 100 ) );
						GetRender()->DrawFilledRect( Gwen::Rect( 17, 0, iLabelWidth + 2, iLabelHeight-1 ) );
						GetRender()->SetDrawColor( Color( 0, 150, 255, 200 ) );
						GetRender()->DrawLinedRect( Gwen::Rect( 17, 0, iLabelWidth + 2, iLabelHeight-1 ) );
					}

					GetRender()->SetDrawColor( Color( 0, 0, 0, 50 ) );

					if ( !bIsRoot )
						GetRender()->DrawFilledRect( Gwen::Rect( 9, iHalfWay, 16-9, 1 ) );

					if ( !bOpen ) return;

					GetRender()->DrawFilledRect( Gwen::Rect( 14 + 8, iLabelHeight, 1, iLastBranch + iHalfWay - iLabelHeight ) );
				}

				void DrawColorDisplay( Controls::Base* control, Gwen::Color color )
				{
					Gwen::Rect rect = control->GetRenderBounds();

					if ( color.a != 255)
					{
						GetRender()->SetDrawColor( Gwen::Color( 255, 255, 255, 255 ) );
						GetRender()->DrawFilledRect( rect );

						GetRender()->SetDrawColor( Gwen::Color( 128, 128, 128, 128 ) );

						GetRender()->DrawFilledRect( Gwen::Rect( 0, 0, rect.w * 0.5, rect.h * 0.5) );
						GetRender()->DrawFilledRect( Gwen::Rect( rect.w * 0.5, rect.h * 0.5, rect.w * 0.5,rect.h * 0.5) );
					}

					GetRender()->SetDrawColor( color );
					GetRender()->DrawFilledRect( rect );

					GetRender()->SetDrawColor( Gwen::Color( 0, 0, 0, 255 ) );
					GetRender()->DrawLinedRect( rect );
				}

				virtual void DrawModalControl( Controls::Base* control )
				{
					if ( control->ShouldDrawBackground() )
					{
						Gwen::Rect rect = control->GetRenderBounds();
						GetRender()->SetDrawColor( m_colModal );
						GetRender()->DrawFilledRect( rect );
					}
				}

				virtual void DrawMenuDivider( Controls::Base* control )
				{
					Gwen::Rect rect = control->GetRenderBounds();
					GetRender()->SetDrawColor( m_colBGDark );
					GetRender()->DrawFilledRect( rect );
					GetRender()->SetDrawColor( m_colControlDarker);
					GetRender()->DrawLinedRect( rect );
				}

				virtual void DrawTreeControl( Controls::Base* control )
				{
					m_texTreeBG.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawWindowCloseButton( Gwen::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled )
				{
					if ( bDisabled )
						return Textures.Window.Close_Disabled.Draw( GetRender(), control->GetRenderBounds() );

					if ( bDepressed )
						return Textures.Window.Close_Down.Draw( GetRender(), control->GetRenderBounds() );

					if ( bHovered )
						return Textures.Window.Close_Hover.Draw( GetRender(), control->GetRenderBounds() );

					Textures.Window.Close.Draw( GetRender(), control->GetRenderBounds() );
				}
		}; 
	}
}
#endif
