/*
	GWEN
	Copyright (c) 2011 Facepunch Studios
	See license in Gwen.h
*/

#pragma once

#include "Gwen/InputHandler.h"
#include "Gwen/Gwen.h"
#include "Gwen/Controls/Canvas.h"

#include <SFML/Graphics.hpp>

namespace Gwen
{
	namespace Input
	{
		class SFML
		{
			public:

				SFML()
				{
					m_Canvas = NULL;
					m_MouseX = 0;
					m_MouseY = 0;
				}

				void Initialize( Gwen::Controls::Canvas* c )
				{
					m_Canvas = c;
				}

				unsigned char TranslateKeyCode( int iKeyCode )
				{
					switch ( iKeyCode )
					{
						case sf::Key::Back:			return Gwen::Key::Backspace;
						case sf::Key::Return:		return Gwen::Key::Return;
						case sf::Key::Escape:		return Gwen::Key::Escape;
						case sf::Key::Tab:			return Gwen::Key::Tab;
						case sf::Key::Space:		return Gwen::Key::Space;
						case sf::Key::Up:			return Gwen::Key::Up;
						case sf::Key::Down:			return Gwen::Key::Down;
						case sf::Key::Left:			return Gwen::Key::Left;
						case sf::Key::Right:		return Gwen::Key::Right;
						case sf::Key::Home:			return Gwen::Key::Home;
						case sf::Key::End:			return Gwen::Key::End;
						case sf::Key::Delete:		return Gwen::Key::Delete;
						case sf::Key::LControl:		return Gwen::Key::Control;
						case sf::Key::LAlt:			return Gwen::Key::Alt;
						case sf::Key::LShift:		return Gwen::Key::Shift;
						case sf::Key::RControl:		return Gwen::Key::Control;
						case sf::Key::RAlt:			return Gwen::Key::Alt;
						case sf::Key::RShift:		return Gwen::Key::Shift;
					}

					return Gwen::Key::Invalid;
				}

				bool ProcessMessage( sf::Event& event )
				{
					if ( !m_Canvas ) return false;

					switch(event.Type)
					{
						case sf::Event::MouseMoved:
							{
								int dx = event.MouseMove.X - m_MouseX;
								int dy = event.MouseMove.Y - m_MouseY;

								m_MouseX = event.MouseMove.X;
								m_MouseY = event.MouseMove.Y;

								m_Canvas->InputMouseMoved( m_MouseX, m_MouseY, dx, dy );
								break;
							}


						case sf::Event::MouseButtonPressed:
						case sf::Event::MouseButtonReleased:
							{
								m_Canvas->InputMouseButton( event.MouseButton.Button, event.Type == sf::Event::MouseButtonPressed );
								break;
							}
							
						case sf::Event::MouseWheelMoved:
							{
								m_Canvas->InputMouseWheel( event.MouseWheel.Delta * 60 );
								break;
							}

						case sf::Event::TextEntered:
							{
								m_Canvas->InputCharacter( event.Text.Unicode );
								break;
							}

						case sf::Event::KeyPressed:
						case sf::Event::KeyReleased:
							{
								bool bPressed = (event.Type == sf::Event::KeyPressed);

								if ( event.Key.Control && bPressed && event.Key.Code >= 'a' && event.Key.Code <= 'z' )
								{
									return m_Canvas->InputCharacter( event.Key.Code );
								}

								unsigned char iKey = TranslateKeyCode( event.Key.Code );

								m_Canvas->InputKey( iKey, bPressed );
								break;

							}
					}

					return false;
				}

				protected:

					Gwen::Controls::Canvas*	m_Canvas;
					int m_MouseX;
					int m_MouseY;

		};
	}
}

