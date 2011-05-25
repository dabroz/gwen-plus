#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"
#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"
#include "Gwen/Renderers/SFML.h"



namespace Gwen 
{
	namespace Renderer 
	{

		SFML::SFML( sf::RenderTarget& target ) : m_Target(target)
		{

		}

		SFML::~SFML()
		{

		}

		void SFML::SetDrawColor( Gwen::Color color )
		{
			m_Color.r = color.r;
			m_Color.g = color.g;
			m_Color.b = color.b;
			m_Color.a = color.a;
		}

		void SFML::DrawFilledRect( Gwen::Rect rect )
		{
			Translate(rect);
			m_Target.Draw( sf::Shape::Rectangle( rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, m_Color ) );
		}

		void SFML::DrawLine( int x, int y, int a, int b )
		{
			Translate( x, y );
			Translate( a, b );
			m_Target.Draw( sf::Shape::Line( x, y, a, b, 1.0f, m_Color ) );
		}

		void SFML::LoadFont( Gwen::Font* font )
		{
			font->realsize = font->size * Scale();

			sf::Font* pFont = new sf::Font();
			if ( !pFont->LoadFromFile( Utility::UnicodeToString( font->facename ), font->realsize ) )
			{
				//
				// Note that SFML can't find system fonts (on its own)
				//
				pFont = NULL;
			}
			
			font->data = pFont;
		}

		void SFML::FreeFont( Gwen::Font* pFont )
		{
			if ( !pFont->data ) return;

			sf::Font* font = ((sf::Font*)pFont->data);
			delete font;
			pFont->data = NULL;
		}

		void SFML::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text )
		{
			Translate( pos.x, pos.y );

			const sf::Font* pSFFont = (sf::Font*)(pFont->data);

			// If the font doesn't exist, or the font size should be changed
			if ( !pSFFont || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			if  ( !pSFFont )
			{
				pSFFont = &(sf::Font::GetDefaultFont());
			}

			sf::String sfStr( text );
			sfStr.SetFont( *pSFFont );
			sfStr.Move( pos.x, pos.y );
			sfStr.SetSize( pFont->realsize );
			sfStr.SetColor( m_Color );

			m_Target.Draw( sfStr );
		}

		Gwen::Point SFML::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text )
		{
			const sf::Font* pSFFont = (sf::Font*)(pFont->data);

			// If the font doesn't exist, or the font size should be changed
			if ( !pSFFont || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			if  ( !pSFFont )
			{
				pSFFont = &(sf::Font::GetDefaultFont());
			}

			sf::String sfStr( text );
			sfStr.SetFont( *pSFFont );
			sfStr.SetSize( pFont->realsize );
			sfStr.SetColor( m_Color );

			sf::FloatRect sz = sfStr.GetRect();
			return Gwen::Point( sz.GetWidth(), sz.GetHeight() );
		}

		void SFML::StartClip()
		{
			Gwen::Rect rect = ClipRegion();

			// OpenGL's coords are from the bottom left
			// so we need to translate them here.
			{
				GLint view[4];
				glGetIntegerv( GL_VIEWPORT, &view[0] );
				rect.y = view[3] - (rect.y + rect.h);
			}

			glScissor( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() );
			glEnable( GL_SCISSOR_TEST );
		};


		void SFML::EndClip()
		{
			glDisable(GL_SCISSOR_TEST);
		};

		void SFML::LoadTexture( Gwen::Texture* pTexture )
		{
			if ( !pTexture ) return;
			if ( pTexture->data ) FreeTexture( pTexture );

			sf::Image* tex = new sf::Image();
			tex->SetSmooth( true );

			if ( !tex->LoadFromFile( pTexture->name.Get() ) )
			{
				delete( tex );
				pTexture->failed = true;
				return;
			}

			pTexture->height = tex->GetHeight();
			pTexture->width = tex->GetWidth();
			pTexture->data = tex;

		};

		void SFML::FreeTexture( Gwen::Texture* pTexture )
		{
			sf::Image* tex = static_cast<sf::Image*>( pTexture->data );

			if ( tex )
			{
				delete tex;
			}

			pTexture->data = NULL;
		}

		void SFML::DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect rect, float u1, float v1, float u2, float v2 )
		{
			const sf::Image* tex = static_cast<sf::Image*>( pTexture->data );

			if ( !tex ) 
			{
				return DrawMissingImage( rect );
			}

			Translate( rect );
			

			sf::Sprite sp( *tex, sf::Vector2f( rect.x, rect.y ) );

			float fW = tex->GetWidth();
			float fH = tex->GetHeight();

			sp.SetSubRect( sf::IntRect( ceil(u1 * fW), ceil(v1 * fH), ceil(u2 * fW), ceil(v2 * fH) ) );				
			sp.Resize( rect.w, rect.h );

			m_Target.Draw(sp);
		};


	
	}
}