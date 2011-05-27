
#include "Gwen/Renderers/OpenGL.h"
#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"

#include <math.h>

#include "GL/GLEW.h"
#include "FreeImage/FreeImage.h"

#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
#define GL_FREEIMAGE_ORDER GL_RGBA
#elif FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_BGR
#define GL_FREEIMAGE_ORDER GL_BGRA
#endif

struct GLFont
{
	GLuint base;
	const GLsizei characterCount;
	const HDC HDCOwner;
	HFONT font;
	int iSpaceWidth;
	GLFont(const wchar_t *fontName, int height, HDC hDC, int fnWeight, GLsizei nCharacters = 256 ) : characterCount(nCharacters), HDCOwner(hDC)
	{
		HFONT	oldfont;									// Used For Good House Keeping

		base = glGenLists(nCharacters);								// Storage For 96 Characters

		font = CreateFont(	height,							// Height Of Font
							0,								// Width Of Font
							0,								// Angle Of Escapement
							0,								// Orientation Angle
							fnWeight,						// Font Weight
							FALSE,							// Italic
							FALSE,							// Underline
							FALSE,							// Strikeout
							DEFAULT_CHARSET,				// Character Set Identifier
							OUT_DEFAULT_PRECIS,					// Output Precision
							CLIP_DEFAULT_PRECIS,			// Clipping Precision
							(height) > (-14) ? DEFAULT_QUALITY : CLEARTYPE_QUALITY,			// Output Quality
							FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
							fontName);					// Font Name

		oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
		
		RECT rctA = {0,0,0,0};
		DrawTextExW( NULL, L"A", -1, &rctA, DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE, 0 );

		RECT rctSpc = {0,0,0,0};
		DrawTextExW( NULL, L"A A", -1, &rctSpc, DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE, 0 );

		iSpaceWidth = rctSpc.right - rctA.right * 2;
		wglUseFontBitmaps(hDC, 32, characterCount, base);				// Builds 96 Characters Starting At Character 32

		SelectObject(hDC, oldfont);							// Selects The Font We Want
		DeleteObject(font);									// Delete The Font
	}

	~ GLFont(GLvoid)									// Delete The Font List
	{
		glDeleteLists(base, characterCount);							// Delete All 96 Characters
		DeleteObject(font);									// Delete The Font
	}

	GLvoid Draw(const Gwen::UnicodeString &text, const Gwen::Point &loc, float scale, HWND window)
	{
		glDisable( GL_BLEND );
		RECT clip = { loc.x, loc.y, 0, 0 };
		HFONT	oldfont = (HFONT)SelectObject(HDCOwner, font);   

		DrawTextExW( HDCOwner, (wchar_t*)text.c_str(), -1, &clip, DT_CALCRECT | DT_LEFT | DT_TOP| DT_SINGLELINE, 0 );
		RECT r;
		GetClientRect(window, &r);

		float x = (float)clip.left;
		float y = (float)clip.bottom - ( clip.bottom - clip.top)/3;


		x /= scale;
		y /= scale;
		
		//rpos.v -= 0.5f;
		glRasterPos2f( x, y );
		glPushAttrib(GL_LIST_BIT);
		glListBase(base - 32);
		glCallLists(text.length(), GL_UNSIGNED_SHORT, text.c_str());
		glPopAttrib();
		
		SelectObject(HDCOwner, oldfont);		

		glEnable ( GL_BLEND );
	}

	int MeasureText(const Gwen::UnicodeString &text, Gwen::Point & point, float scale)
	{
		int ret = 0;
		HFONT	oldfont = (HFONT)SelectObject(HDCOwner, font);   

		/*
		RECT rct =  { 0, 0, 0, 0};
		if((ret = DrawTextExW( HDCOwner, (wchar_t*)text.c_str(), text.length(), &rct, DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE, 0 )))
		{
			point.x = (float)(rct.right) / scale;
			point.y = (float)(rct.bottom) / scale;
			
			for (int i=text.length()-1; i>=0 && text[i] == L' '; i-- )
			{
				//point.x += iSpaceWidth;
			}
		}*/
		SIZE s;
		if(GetTextExtentPoint32(HDCOwner, text.c_str(), text.length(), &s))
		{
			point.x = s.cx;
			point.y = s.cy;
			ret = TRUE;
		}
		SelectObject(HDCOwner, oldfont);					
		return ret;
	}
};


namespace Gwen
{
	namespace Renderer
	{
		OpenGL::OpenGL(HDC hdc, HWND _window) : ghdc(hdc), window(_window),
			m_iVertNum(0)
		{
			::FreeImage_Initialise();

			for ( int i=0; i<MaxVerts; i++ )
			{
				m_Vertices[ i ].z = 0.5f;
			}

			m_DefaultFont = new GLFont(L"Courier New", 24, hdc, FW_NORMAL);
		}

		OpenGL::~OpenGL()
		{
			::FreeImage_DeInitialise();
			delete m_DefaultFont;
		}

		void OpenGL::Begin()
		{
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glAlphaFunc( GL_GREATER, 1.0f );	
			glEnable ( GL_BLEND );
		}

		void OpenGL::End()
		{
			Flush();
		}

		void OpenGL::DrawLine( int x, int y, int a, int b )
		{
			Translate( x, y );
			Translate( a, b );

			//OpenGL::Pen pen( m_Colour, 1.0f );
			//graphics->DrawLine( &pen, x, y, a, b );			
		}

		void OpenGL::Flush()
		{
			if ( m_iVertNum == 0 ) return;

			glVertexPointer( 3, GL_FLOAT,  sizeof(Vertex), (void*) &m_Vertices[0].x );
			glEnableClientState( GL_VERTEX_ARRAY );

			glColorPointer( 4, GL_UNSIGNED_BYTE, sizeof(Vertex), (void*)&m_Vertices[0].r );
			glEnableClientState( GL_COLOR_ARRAY );

			glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), (void*) &m_Vertices[0].u );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );

			glDrawArrays( GL_TRIANGLES, 0, (GLsizei) m_iVertNum );

			m_iVertNum = 0;
			glFlush();
		}

		void OpenGL::AddVert( int x, int y )
		{
			if ( m_iVertNum >= MaxVerts-1 )
			{
				Flush();
			}

			m_Vertices[ m_iVertNum ].x = (float)x;
			m_Vertices[ m_iVertNum ].y = (float)y;
			m_Vertices[ m_iVertNum ].r = m_Color.r;
			m_Vertices[ m_iVertNum ].g = m_Color.g;
			m_Vertices[ m_iVertNum ].b = m_Color.b;
			m_Vertices[ m_iVertNum ].a = m_Color.a;

			m_iVertNum++;
		}

		void OpenGL::AddVert( int x, int y, float u, float v )
		{
			if ( m_iVertNum >= MaxVerts-1 )
			{
				Flush();
			}

			m_Vertices[ m_iVertNum ].x = (float)x;
			m_Vertices[ m_iVertNum ].y = (float)y;
			m_Vertices[ m_iVertNum ].u = u;
			m_Vertices[ m_iVertNum ].v = v;

			m_Vertices[ m_iVertNum ].r = m_Color.r;
			m_Vertices[ m_iVertNum ].g = m_Color.g;
			m_Vertices[ m_iVertNum ].b = m_Color.b;
			m_Vertices[ m_iVertNum ].a = m_Color.a;

			m_iVertNum++;
		}

		void OpenGL::DrawFilledRect( Gwen::Rect rect )
		{
			GLboolean texturesOn;

			glGetBooleanv(GL_TEXTURE_2D, &texturesOn);
			if ( texturesOn )
			{
				Flush();
				glDisable(GL_TEXTURE_2D);
			}	

			Translate( rect );

			AddVert( rect.x, rect.y );
			AddVert( rect.x+rect.w, rect.y );
			AddVert( rect.x, rect.y + rect.h );

			AddVert( rect.x+rect.w, rect.y );
			AddVert( rect.x+rect.w, rect.y+rect.h );
			AddVert( rect.x, rect.y + rect.h );
		}

		void OpenGL::SetDrawColor(Gwen::Color color)
		{
			glColor4ubv( (GLubyte*)&color );
			m_Color = color;
		}

		void OpenGL::StartClip()
		{
			Flush();
			const Gwen::Rect& rect = ClipRegion();
			
			
			/*
			r.left = ceil( ((float)rect.x) * Scale() );
			r.right = ceil(((float)(rect.x + rect.w)) * Scale()) + 1;
			r.top = ceil( (float)rect.y * Scale() );
			r.bottom = ceil( ((float)(rect.y + rect.h)) * Scale() ) + 1;*/
#ifndef TEST_DISABLE_SCISORS
			RECT r;
			GetClientRect(window, &r);

			RECT clip = { rect.x, rect.y, rect.x + rect.w, rect.y + rect.h } ;
			GLint x = ceil( ((float)clip.left) * Scale() );
			GLsizei w = ceil(((float)(clip.right - clip.left)) * Scale()) + 1;
			GLint y = ceil( (float)(r.bottom - clip.bottom) * Scale() );
			GLsizei h = ceil( ((float)(clip.bottom - clip.top)) * Scale() ) + 1;
			//glViewport(x, y, w, h);
			glLoadIdentity();
			glScissor(x, y, w, h); 
			glEnable(GL_SCISSOR_TEST);
#endif
		}

		void OpenGL::EndClip()
		{
			Flush();
#ifndef TEST_DISABLE_SCISORS
			glDisable(GL_SCISSOR_TEST);
#endif
			//RECT r;
			//::GetClientRect(window, &r);
			//glViewport(0, 0, r.right - r.left, r.bottom - r.top);
		}

		void OpenGL::DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect rect, float u1, float v1, float u2, float v2 )
		{
			
			//m_DefaultFont->Draw(pTexture->name.GetUnicode().c_str());
			GLuint tex;
			// Missing image, not loaded properly?
			if ( ! ( tex = *((GLuint *)&pTexture->data) ) )
			{
				return DrawMissingImage( rect );
			}

			Translate( rect );
			GLuint boundtex;

			GLboolean texturesOn;
			glGetBooleanv(GL_TEXTURE_2D, &texturesOn);
			glGetIntegerv(GL_TEXTURE_BINDING_2D, (GLint *)&boundtex);
			if ( !texturesOn || tex != boundtex )
			{
				Flush();
				glBindTexture( GL_TEXTURE_2D, tex );
				glEnable(GL_TEXTURE_2D);
			}		

			AddVert( rect.x, rect.y,			u1, v1 );
			AddVert( rect.x+rect.w, rect.y,		u2, v1 );
			AddVert( rect.x, rect.y + rect.h,	u1, v2 );

			AddVert( rect.x+rect.w, rect.y,		u2, v1 );
			AddVert( rect.x+rect.w, rect.y+rect.h, u2, v2 );
			AddVert( rect.x, rect.y + rect.h, u1, v2 );			
		}

		void OpenGL::LoadTexture( Gwen::Texture* pTexture )
		{
			const wchar_t *wFileName = pTexture->name.GetUnicode().c_str();
			FREE_IMAGE_FORMAT imageFormat;
			FIBITMAP * bits;
			if(
				((imageFormat = FreeImage_GetFileTypeU(wFileName)) != FIF_UNKNOWN ||
				(imageFormat = FreeImage_GetFIFFromFilenameU(wFileName)) != FIF_UNKNOWN ) &&
				(bits = FreeImage_LoadU(imageFormat, wFileName)) != 0)
			{
				FIBITMAP * bits32 = FreeImage_ConvertTo32Bits(bits);
				FreeImage_Unload(bits);
				if(bits32)
				{
					::FreeImage_FlipVertical(bits32);
					glGenTextures(1, (GLuint*)&pTexture->data);
					glBindTexture(GL_TEXTURE_2D, *((GLuint*)&pTexture->data));
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexImage2D(GL_TEXTURE_2D, 
						0, 
						GL_RGBA,
						(GLsizei)(pTexture->width = FreeImage_GetWidth(bits32)),
						(GLsizei)(pTexture->height = FreeImage_GetHeight(bits32)),
						0, 
						GL_FREEIMAGE_ORDER, GL_UNSIGNED_BYTE, 
						(const GLvoid*)FreeImage_GetBits(bits32));

					FreeImage_Unload(bits32);
				}
			}
		}

		void OpenGL::FreeTexture( Gwen::Texture* pTexture )
		{
			glDeleteTextures(1, (const GLuint *)&pTexture->data);
			pTexture->data = 0;
			return;
		}

		void OpenGL::Release()
		{
			Font::List::iterator it = m_FontList.begin();

			while ( it != m_FontList.end() )
			{
				FreeFont( *it );
				it = m_FontList.begin();
			}
		}
	}
}