
#include "Gwen/Renderers/OpenGL_DebugFont.h"
#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"

#include <math.h>
#include "GL/glew.h"

#include "FontData.h"

namespace Gwen
{
	namespace Renderer
	{
		OpenGL_DebugFont::OpenGL_DebugFont()
		{
			m_fLetterSpacing = 0.6f;
			m_fFontScale[0] = 1.1f;
			m_fFontScale[1] = 1.0f;

			m_pFontTexture = new Gwen::Texture();

			// Create a little texture pointer..
			GLuint* pglTexture = new GLuint;

			// Sort out our GWEN texture
			m_pFontTexture->data = pglTexture;
			m_pFontTexture->width = 256;
			m_pFontTexture->height = 256;

			// Create the opengl texture
			glGenTextures( 1, pglTexture );
			glBindTexture( GL_TEXTURE_2D, *pglTexture );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

			GLenum format = GL_RGB;
			unsigned char* texdata = new unsigned char[256*256*4];
			for (int i=0;i<256*256;i++)
			{
				texdata[i*4] = sGwenFontData[i*3];
				texdata[i*4+1] = sGwenFontData[i*3+1];
				texdata[i*4+2] = sGwenFontData[i*3+2];
				if (sGwenFontData[i*3]+sGwenFontData[i*3+1]+sGwenFontData[i*3+2] )
				{
					texdata[i*4+3] = 255;	
				} 
				else
				{
					texdata[i*4+3] = 0;
				}
			}

			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_pFontTexture->width, m_pFontTexture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)texdata );

		}

		OpenGL_DebugFont::~OpenGL_DebugFont()
		{
			FreeTexture( m_pFontTexture );
			delete m_pFontTexture;
		}

		void OpenGL_DebugFont::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text )
		{
			float fSize = pFont->size * Scale();

			if ( !text.length() )
				return;

			Gwen::String converted_string = Gwen::Utility::UnicodeToString( text );

			for ( int i=0; i<text.length(); i++ )
			{
				wchar_t chr = text[i];

				if ( chr == ' ' ) continue;

				Gwen::Rect r( pos.x + i * fSize * m_fFontScale[0] * m_fLetterSpacing, pos.y, (fSize * m_fFontScale[0]), fSize * m_fFontScale[1] );
				
				if ( m_pFontTexture )
				{
					char ch = converted_string[i]-32;
					float uv_texcoords[8]={0.,0.,1.,1.};

					if ( ch >= 0 )
					{
						float cx=float(ch%16) * float(1./16.f);
						float cy=float(ch/16) * float(1./16.f);

						uv_texcoords[0] = cx;			
						uv_texcoords[1] = float(1-cy-1./16.f);
						//uv_texcoords[2] = float(cx+1./16.f);	
						//uv_texcoords[3] = float(1-cy-1./16.f);
						uv_texcoords[4] = float(cx+1./16.f);	
						uv_texcoords[5] = float(1-cy);

						//uv_texcoords[6] = cx;
						//uv_texcoords[7] = float(1-cy);
					}

					DrawTexturedRect( m_pFontTexture, r, uv_texcoords[0], uv_texcoords[5], uv_texcoords[4], uv_texcoords[1] );
				} 
				else
				{
					DrawFilledRect( r );
				}
			}

		}

		Gwen::Point OpenGL_DebugFont::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text )
		{
			Gwen::Point p;
			p.x = pFont->size * Scale() * (float)(text.length()-1) * m_fFontScale[0] * m_fLetterSpacing;
			p.x += pFont->size * Scale() * m_fFontScale[0];
			p.y = pFont->size * Scale() * m_fFontScale[1];
			return p;
		}

	}
}