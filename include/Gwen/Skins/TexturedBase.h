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

				Texturing::Bordered	m_texGenericPanel;

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
					Texturing::Bordered StatusBar;
					Texturing::Bordered Selection;

					struct /* Window */
					{
						Texturing::Single Close;
						Texturing::Single Close_Hover;
						Texturing::Single Close_Down;
						Texturing::Single Close_Disabled;

					} Window;

					struct  /* ProgressBar */
					{
						Texturing::Bordered Back;
						Texturing::Bordered Front;

					} ProgressBar;

					struct  /* Scroller */
					{
						Texturing::Bordered TrackV;
						Texturing::Bordered ButtonV_Normal;
						Texturing::Bordered ButtonV_Hover;
						Texturing::Bordered ButtonV_Down;
						Texturing::Bordered ButtonV_Disabled;
						Texturing::Bordered TrackH;
						Texturing::Bordered ButtonH_Normal;
						Texturing::Bordered ButtonH_Hover;
						Texturing::Bordered ButtonH_Down;
						Texturing::Bordered ButtonH_Disabled;

						struct /* Button */
						{
							Texturing::Bordered	Normal[4];
							Texturing::Bordered	Hover[4];
							Texturing::Bordered	Down[4];
							Texturing::Bordered	Disabled[4];
							
						} Button;

					} Scroller;

					struct /* Menu */
					{
						Texturing::Single RightArrow;

					} Menu;

					struct /* Input */
					{
						struct /* ListBox */
						{
							Texturing::Bordered Background;
							Texturing::Bordered Hovered;

							Texturing::Bordered EvenLine;
							Texturing::Bordered OddLine;
							Texturing::Bordered EvenLineSelected;
							Texturing::Bordered OddLineSelected;

						} ListBox;

						struct /* UpDown */
						{
							struct /* Up */
							{
								Texturing::Single Normal;
								Texturing::Single Hover;
								Texturing::Single Down;
								Texturing::Single Disabled;

							} Up;

							struct /* Down */
							{
								Texturing::Single Normal;
								Texturing::Single Hover;
								Texturing::Single Down;
								Texturing::Single Disabled;

							} Down;

						} UpDown;

						struct /* ComboBox */
						{
							Texturing::Bordered Normal;
							Texturing::Bordered Hover;
							Texturing::Bordered Down;
							Texturing::Bordered Disabled;

							struct /* Button */
							{
								Texturing::Single Normal;
								Texturing::Single Hover;
								Texturing::Single Down;
								Texturing::Single Disabled;

							} Button;

						} ComboBox;

						struct /* Slider */
						{
							struct /* H */
							{
								Texturing::Single Normal;
								Texturing::Single Hover;
								Texturing::Single Down;
								Texturing::Single Disabled;
							} H;

							struct /* Slider */
							{
								Texturing::Single Normal;
								Texturing::Single Hover;
								Texturing::Single Down;
								Texturing::Single Disabled;
							} V;

						} Slider;

					} Input;

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

					Colors.Window.TitleActive	= GetRender()->PixelColour( &m_Texture, 4 + 8 * 0, 508, Color( 255, 0, 0 ) );
					Colors.Window.TitleInactive	= GetRender()->PixelColour( &m_Texture, 4 + 8 * 1, 508, Color( 255, 255, 0) );
					Colors.Button.Normal		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 2, 508, Color( 255, 255, 0) );
					Colors.Button.Hover			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 3, 508, Color( 255, 255, 0) );
					Colors.Button.Down			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 2, 500, Color( 255, 255, 0) );
					Colors.Button.Disabled		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 3, 500, Color( 255, 255, 0) );
					Colors.Tab.Active.Normal		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 4, 508, Color( 255, 255, 0) );
					Colors.Tab.Active.Hover			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 5, 508, Color( 255, 255, 0) );
					Colors.Tab.Active.Down			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 4, 500, Color( 255, 255, 0) );
					Colors.Tab.Active.Disabled		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 5, 500, Color( 255, 255, 0) );
					Colors.Tab.Inactive.Normal		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 6, 508, Color( 255, 255, 0) );
					Colors.Tab.Inactive.Hover		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 7, 508, Color( 255, 255, 0) );
					Colors.Tab.Inactive.Down		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 6, 500, Color( 255, 255, 0) );
					Colors.Tab.Inactive.Disabled	= GetRender()->PixelColour( &m_Texture, 4 + 8 * 7, 500, Color( 255, 255, 0) );
					Colors.Label.Default			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 8, 508, Color( 255, 255, 0) );
					Colors.Label.Bright				= GetRender()->PixelColour( &m_Texture, 4 + 8 * 9, 508, Color( 255, 255, 0) );
					Colors.Label.Dark				= GetRender()->PixelColour( &m_Texture, 4 + 8 * 8, 500, Color( 255, 255, 0) );
					Colors.Label.Highlight			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 9, 500, Color( 255, 255, 0) );
		
					Colors.Tree.Lines				= GetRender()->PixelColour( &m_Texture, 4 + 8 * 10, 508, Color( 255, 255, 0) );
					Colors.Tree.Normal				= GetRender()->PixelColour( &m_Texture, 4 + 8 * 11, 508, Color( 255, 255, 0) );
					Colors.Tree.Hover				= GetRender()->PixelColour( &m_Texture, 4 + 8 * 10, 500, Color( 255, 255, 0) );
					Colors.Tree.Selected			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 11, 500, Color( 255, 255, 0) );

					Colors.Properties.Line_Normal		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 12, 508, Color( 255, 255, 0) );
					Colors.Properties.Line_Selected		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 13, 508, Color( 255, 255, 0) );
					Colors.Properties.Line_Hover		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 12, 500, Color( 255, 255, 0) );
					Colors.Properties.Title				= GetRender()->PixelColour( &m_Texture, 4 + 8 * 13, 500, Color( 255, 255, 0) );

					Colors.Properties.Column_Normal		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 14, 508, Color( 255, 255, 0) );
					Colors.Properties.Column_Selected	= GetRender()->PixelColour( &m_Texture, 4 + 8 * 15, 508, Color( 255, 255, 0) );
					Colors.Properties.Column_Hover		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 14, 500, Color( 255, 255, 0) );
					Colors.Properties.Border			= GetRender()->PixelColour( &m_Texture, 4 + 8 * 15, 500, Color( 255, 255, 0) );

					Colors.Properties.Label_Normal		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 16, 508, Color( 255, 255, 0) );
					Colors.Properties.Label_Selected	= GetRender()->PixelColour( &m_Texture, 4 + 8 * 17, 508, Color( 255, 255, 0) );
					Colors.Properties.Label_Hover		= GetRender()->PixelColour( &m_Texture, 4 + 8 * 16, 500, Color( 255, 255, 0) );
	
					m_texWindow.Init			( &m_Texture, 0, 0, 127,		127,	Margin( 8, 32, 8, 8 ) );
					m_texWindow_Inactive.Init	( &m_Texture, 128, 0, 127,		127,	Margin( 8, 32, 8, 8 ) );
					m_texGenericPanel.Init		( &m_Texture, 256, 0,	127,	127,	Margin( 16,	16, 16, 16 ) );
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

					for ( int i=0; i<4; i++ )
					{
						Textures.Scroller.Button.Normal[i].Init		( &m_Texture, 464 + 0, 208 + i * 16, 15, 15, Margin( 2, 2, 2, 2 ) );
						Textures.Scroller.Button.Hover[i].Init		( &m_Texture, 480, 208 + i * 16, 15, 15, Margin( 2, 2, 2, 2 ) );
						Textures.Scroller.Button.Down[i].Init		( &m_Texture, 464, 272 + i * 16, 15, 15, Margin( 2, 2, 2, 2 ) );
						Textures.Scroller.Button.Disabled[i].Init	( &m_Texture, 480 + 48, 272 + i * 16, 15, 15, Margin( 2, 2, 2, 2 ) );
					}

					Textures.Scroller.TrackV.Init				( &m_Texture, 384,			208, 15, 127, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonV_Normal.Init		( &m_Texture, 384 + 16,		208, 15, 127, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonV_Hover.Init		( &m_Texture, 384 + 32,		208, 15, 127, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonV_Down.Init			( &m_Texture, 384 + 48,		208, 15, 127, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonV_Disabled.Init		( &m_Texture, 384 + 64,		208, 15, 127, Margin( 4, 4, 4, 4 ) );

					Textures.Scroller.TrackH.Init				( &m_Texture, 384,	128,		127, 15, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonH_Normal.Init		( &m_Texture, 384,	128 + 16,	127, 15, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonH_Hover.Init		( &m_Texture, 384,	128 + 32,	127, 15, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonH_Down.Init			( &m_Texture, 384,	128 + 48,	127, 15, Margin( 4, 4, 4, 4 ) );
					Textures.Scroller.ButtonH_Disabled.Init		( &m_Texture, 384,	128 + 64,	127, 15, Margin( 4, 4, 4, 4 ) );

					Textures.Menu.RightArrow.Init				( &m_Texture, 464, 112, 15, 15 );

					Textures.Input.ListBox.Background.Init		( &m_Texture, 256,	256, 63, 127, Margin( 8, 8, 8, 8 ) );
					Textures.Input.ListBox.Hovered.Init			( &m_Texture, 320,	320, 31, 31, Margin( 8, 8, 8, 8 ) );
					Textures.Input.ListBox.EvenLine.Init		( &m_Texture, 352,  256, 31, 31, Margin( 8, 8, 8, 8 ) );
					Textures.Input.ListBox.OddLine.Init			( &m_Texture, 352,  288, 31, 31, Margin( 8, 8, 8, 8 ) );
					Textures.Input.ListBox.EvenLineSelected.Init( &m_Texture, 320,	270, 31, 31, Margin( 8, 8, 8, 8 ) );
					Textures.Input.ListBox.OddLineSelected.Init	( &m_Texture, 320,	288, 31, 31, Margin( 8, 8, 8, 8 ) );

					Textures.Input.ComboBox.Normal.Init			 ( &m_Texture, 384,	336,	127, 31, Margin( 8, 8, 32, 8 ) );
					Textures.Input.ComboBox.Hover.Init			 ( &m_Texture, 384,	336+32, 127, 31, Margin( 8, 8, 32, 8 ) );
					Textures.Input.ComboBox.Down.Init			 ( &m_Texture, 384,	336+64, 127, 31, Margin( 8, 8, 32, 8 ) );
					Textures.Input.ComboBox.Disabled.Init		 ( &m_Texture, 384,	336+96, 127, 31, Margin( 8, 8, 32, 8 ) );

					Textures.Input.ComboBox.Button.Normal.Init			 ( &m_Texture, 496,	272,	15, 15 );
					Textures.Input.ComboBox.Button.Hover.Init			 ( &m_Texture, 496,	272+16, 15, 15 );
					Textures.Input.ComboBox.Button.Down.Init			 ( &m_Texture, 496,	272+32, 15, 15 );
					Textures.Input.ComboBox.Button.Disabled.Init		 ( &m_Texture, 496,	272+48, 15, 15 );

					Textures.Input.UpDown.Up.Normal.Init		( &m_Texture, 384,		112,	7, 7 );
					Textures.Input.UpDown.Up.Hover.Init			( &m_Texture, 384+8,	112,	7, 7 );
					Textures.Input.UpDown.Up.Down.Init			( &m_Texture, 384+16,	112,	7, 7 );
					Textures.Input.UpDown.Up.Disabled.Init		( &m_Texture, 384+24,	112,	7, 7 );

					Textures.Input.UpDown.Down.Normal.Init		( &m_Texture, 384,		120,	7, 7 );
					Textures.Input.UpDown.Down.Hover.Init		( &m_Texture, 384+8,	120,	7, 7 );
					Textures.Input.UpDown.Down.Down.Init		( &m_Texture, 384+16,	120,	7, 7 );
					Textures.Input.UpDown.Down.Disabled.Init	( &m_Texture, 384+24,	120,	7, 7 );

					Textures.ProgressBar.Back.Init		 ( &m_Texture, 384,	0, 31, 31, Margin( 8, 8, 8, 8 ) );
					Textures.ProgressBar.Front.Init		 ( &m_Texture, 384+32,	0, 31, 31, Margin( 8, 8, 8, 8 ) );

					Textures.Input.Slider.H.Normal.Init			 ( &m_Texture, 416,	32,	15, 15 );
					Textures.Input.Slider.H.Hover.Init			 ( &m_Texture, 416,	32+16, 15, 15 );
					Textures.Input.Slider.H.Down.Init			 ( &m_Texture, 416,	32+32, 15, 15 );
					Textures.Input.Slider.H.Disabled.Init		 ( &m_Texture, 416,	32+48, 15, 15 );

					Textures.Input.Slider.V.Normal.Init			 ( &m_Texture, 416+16,	32,	15, 15 );
					Textures.Input.Slider.V.Hover.Init			 ( &m_Texture, 416+16,	32+16, 15, 15 );
					Textures.Input.Slider.V.Down.Init			 ( &m_Texture, 416+16,	32+32, 15, 15 );
					Textures.Input.Slider.V.Disabled.Init		 ( &m_Texture, 416+16,	32+48, 15, 15 );

					Textures.StatusBar.Init		 ( &m_Texture, 128, 288, 127, 31, Margin( 8, 8, 8, 8 ) );
					Textures.Selection.Init		 ( &m_Texture, 384, 32, 31, 31, Margin( 4, 4, 4, 4 ) );
				}


				virtual void DrawButton( Gwen::Controls::Base* control, bool bDepressed, bool bHovered, bool bDisabled )
				{
					if ( bDisabled )	return m_texButton_Dead.Draw( GetRender(), control->GetRenderBounds() );
					if ( bDepressed )	return m_texButton_Pressed.Draw( GetRender(), control->GetRenderBounds() );
					if ( bHovered )		return m_texButton_Hovered.Draw( GetRender(), control->GetRenderBounds() );
					
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

				virtual void DrawMenuRightArrow( Controls::Base* control )
				{
					Textures.Menu.RightArrow.Draw( GetRender(), control->GetRenderBounds() );
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
					if ( isHorizontal )
						Textures.Scroller.TrackH.Draw( GetRender(), control->GetRenderBounds() );
					else
						Textures.Scroller.TrackV.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawScrollBarBar( Controls::Base* control, bool bDepressed, bool isHovered, bool isHorizontal  )
				{
					if ( !isHorizontal )
					{
						if ( control->IsDisabled() )
							return Textures.Scroller.ButtonV_Disabled.Draw( GetRender(), control->GetRenderBounds() );

						if ( bDepressed )
							return Textures.Scroller.ButtonV_Down.Draw( GetRender(), control->GetRenderBounds() );

						if ( isHovered )
							return Textures.Scroller.ButtonV_Hover.Draw( GetRender(), control->GetRenderBounds() );

						return Textures.Scroller.ButtonV_Normal.Draw( GetRender(), control->GetRenderBounds() );
					}

					if ( control->IsDisabled() )
						return Textures.Scroller.ButtonH_Disabled.Draw( GetRender(), control->GetRenderBounds() );

					if ( bDepressed )
						return Textures.Scroller.ButtonH_Down.Draw( GetRender(), control->GetRenderBounds() );

					if ( isHovered )
						return Textures.Scroller.ButtonH_Hover.Draw( GetRender(), control->GetRenderBounds() );
	
					return Textures.Scroller.ButtonH_Normal.Draw( GetRender(), control->GetRenderBounds() );
				}


				virtual void DrawProgressBar( Gwen::Controls::Base* control, bool isHorizontal, float progress)
				{
					Gwen::Rect rect = control->GetRenderBounds();
					Gwen::Color FillColour( 0, 211, 40, 255 );

					if ( isHorizontal )
					{
						Textures.ProgressBar.Back.Draw( GetRender(), rect );
						rect.w *= progress;
						Textures.ProgressBar.Front.Draw( GetRender(), rect );
					}
					else
					{
						Textures.ProgressBar.Back.Draw( GetRender(), rect );
						rect.y += rect.h * (1-progress);
						rect.h *= progress;
						Textures.ProgressBar.Front.Draw( GetRender(), rect );
					}
				}
		 
				virtual void DrawListBox( Gwen::Controls::Base* control )
				{
					return Textures.Input.ListBox.Background.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawListBoxLine( Gwen::Controls::Base* control, bool bSelected, bool bEven )
				{
					if ( bSelected )
						if ( bEven )
							return Textures.Input.ListBox.EvenLineSelected.Draw( GetRender(), control->GetRenderBounds() );
						else 
							return Textures.Input.ListBox.OddLineSelected.Draw( GetRender(), control->GetRenderBounds() );

					if ( control->IsHovered() )
							return Textures.Input.ListBox.Hovered.Draw( GetRender(), control->GetRenderBounds() );

					if ( bEven )
						return Textures.Input.ListBox.EvenLine.Draw( GetRender(), control->GetRenderBounds() );

					return Textures.Input.ListBox.OddLine.Draw( GetRender(), control->GetRenderBounds() );
				}
				
				void DrawSliderNotchesH( Gwen::Rect rect, int numNotches, int dist )
				{
					if ( numNotches == 0 ) return;

					float iSpacing = (float)rect.w / (float)numNotches;
					for ( int i=0; i<numNotches+1; i++ )
					{
						GetRender()->DrawFilledRect( Gwen::Rect( rect.x + iSpacing * i, rect.y + dist - 2, 1, 5 ) );
					}
				}

				void DrawSliderNotchesV( Gwen::Rect rect, int numNotches, int dist )
				{
					if ( numNotches == 0 ) return;

					float iSpacing = (float)rect.h / (float)numNotches;
					for ( int i=0; i<numNotches+1; i++ )
					{
						GetRender()->DrawFilledRect( Gwen::Rect( rect.x + dist - 1, rect.y + iSpacing * i, 5, 1 ) );
					}
				}
				
				virtual void DrawSlider( Gwen::Controls::Base* control, bool bIsHorizontal, int numNotches, int barSize )
				{
					if ( bIsHorizontal )
					{
						Gwen::Rect rect = control->GetRenderBounds();
						rect.x += barSize*0.5;
						rect.w -= barSize;
						rect.y += rect.h*0.5-1;
						rect.h = 1;
						GetRender()->SetDrawColor( Gwen::Color( 0, 0, 0, 100 ) );
						DrawSliderNotchesH( rect, numNotches, barSize * 0.5 );
						return GetRender()->DrawFilledRect( rect );
					}

					Gwen::Rect rect = control->GetRenderBounds();
					rect.y += barSize*0.5;
					rect.h -= barSize;
					rect.x += rect.w*0.5-1;
					rect.w = 1;
					GetRender()->SetDrawColor( Gwen::Color( 0, 0, 0, 100 ) );
					DrawSliderNotchesV( rect, numNotches, barSize * 0.4 );
					return GetRender()->DrawFilledRect( rect );
				}

				virtual void DrawComboBox( Gwen::Controls::Base* control, bool bDown, bool bMenuOpen )
				{
					if ( control->IsDisabled() )
						return Textures.Input.ComboBox.Disabled.Draw( GetRender(), control->GetRenderBounds() );

					if ( bDown || bMenuOpen )
						return Textures.Input.ComboBox.Down.Draw( GetRender(), control->GetRenderBounds() );

					if ( control->IsHovered() )
						return Textures.Input.ComboBox.Hover.Draw( GetRender(), control->GetRenderBounds() );

					Textures.Input.ComboBox.Normal.Draw( GetRender(), control->GetRenderBounds() );
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

				virtual void DrawScrollButton( Gwen::Controls::Base* control, int iDirection, bool bDepressed, bool bHovered, bool bDisabled )
				{
					int i = 0;
					if ( iDirection == Pos::Top ) i = 1;
					if ( iDirection == Pos::Right ) i = 2;
					if ( iDirection == Pos::Bottom ) i = 3;

					if ( bDisabled )
						return Textures.Scroller.Button.Disabled[i].Draw( GetRender(), control->GetRenderBounds() );

					if ( bDepressed )
						return Textures.Scroller.Button.Down[i].Draw( GetRender(), control->GetRenderBounds() );

					if ( bHovered )
						return Textures.Scroller.Button.Hover[i].Draw( GetRender(), control->GetRenderBounds() );

					return Textures.Scroller.Button.Normal[i].Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawComboDownArrow( Gwen::Controls::Base* control, bool bHovered, bool bDown, bool bMenuOpen, bool bDisabled )
				{	
					if ( bDisabled )
						return Textures.Input.ComboBox.Button.Disabled.Draw( GetRender(), control->GetRenderBounds() );

					if ( bDown || bMenuOpen )
						return Textures.Input.ComboBox.Button.Down.Draw( GetRender(), control->GetRenderBounds() );

					if ( bHovered )
						return Textures.Input.ComboBox.Button.Hover.Draw( GetRender(), control->GetRenderBounds() );

					Textures.Input.ComboBox.Button.Normal.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawNumericUpDownButton( Gwen::Controls::Base* control, bool bDepressed, bool bUp )
				{
					if ( bUp )
					{
						if ( control->IsDisabled() )	return Textures.Input.UpDown.Up.Disabled.DrawCenter( GetRender(), control->GetRenderBounds() );
						if ( bDepressed )				return Textures.Input.UpDown.Up.Down.DrawCenter( GetRender(), control->GetRenderBounds() );
						if ( control->IsHovered() )		return Textures.Input.UpDown.Up.Hover.DrawCenter( GetRender(), control->GetRenderBounds() );
						return Textures.Input.UpDown.Up.Normal.DrawCenter( GetRender(), control->GetRenderBounds() );
					}

					if ( control->IsDisabled() )	return Textures.Input.UpDown.Down.Disabled.DrawCenter( GetRender(), control->GetRenderBounds() );
					if ( bDepressed )				return Textures.Input.UpDown.Down.Down.DrawCenter( GetRender(), control->GetRenderBounds() );
					if ( control->IsHovered() )		return Textures.Input.UpDown.Down.Hover.DrawCenter( GetRender(), control->GetRenderBounds() );
					return Textures.Input.UpDown.Down.Normal.DrawCenter( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawStatusBar( Controls::Base* control )
				{
					Textures.StatusBar.Draw( GetRender(), control->GetRenderBounds() );
				}

				virtual void DrawTreeButton( Controls::Base* control, bool bOpen )
				{
					Gwen::Rect rect = control->GetRenderBounds();

					if ( bOpen )
						m_TreeMinus.Draw( GetRender(), rect );
					else
						m_TreePlus.Draw( GetRender(), rect );
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

				virtual void DrawSlideButton( Gwen::Controls::Base* control, bool bDepressed, bool bHorizontal )
				{
					if ( !bHorizontal )
					{
						if ( control->IsDisabled() )	return Textures.Input.Slider.V.Disabled.DrawCenter( GetRender(), control->GetRenderBounds() );
						if ( bDepressed )				return Textures.Input.Slider.V.Down.DrawCenter( GetRender(), control->GetRenderBounds() );
						if ( control->IsHovered() )		return Textures.Input.Slider.V.Hover.DrawCenter( GetRender(), control->GetRenderBounds() );

						return Textures.Input.Slider.V.Normal.DrawCenter( GetRender(), control->GetRenderBounds() );
					}

					if ( control->IsDisabled() )	return Textures.Input.Slider.H.Disabled.DrawCenter( GetRender(), control->GetRenderBounds() );
					if ( bDepressed )				return Textures.Input.Slider.H.Down.DrawCenter( GetRender(), control->GetRenderBounds() );
					if ( control->IsHovered() )		return Textures.Input.Slider.H.Hover.DrawCenter( GetRender(), control->GetRenderBounds() );

					Textures.Input.Slider.H.Normal.DrawCenter( GetRender(), control->GetRenderBounds() );
				}

				void DrawTreeNode( Controls::Base* ctrl, bool bOpen, bool bSelected, int iLabelHeight, int iLabelWidth, int iHalfWay, int iLastBranch, bool bIsRoot )
				{
					if ( bSelected )
					{
						Textures.Selection.Draw( GetRender(), Gwen::Rect( 17, 0, iLabelWidth + 2, iLabelHeight-1 ) );
					}

					Base::DrawTreeNode( ctrl, bOpen, bSelected, iLabelHeight, iLabelWidth, iHalfWay, iLastBranch, bIsRoot );
				}
		}; 
	}
}
#endif
