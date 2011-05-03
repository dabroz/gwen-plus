
#include <windows.h>
#include <d3d9.h>
#include <D3dx9core.h>

#include "Gwen/Renderers/OpenGL.h"
#include "Gwen/Utility.h"
#include "Gwen/Font.h"
#include "Gwen/Texture.h"

#include <math.h>

#include "GL/GLEW.h"


#include "FreeImage/FreeImage.h"

//#define TEST_DISABLE_SCISORS

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
		RECT clip = { loc.x, loc.y, 0, 0 };
		HFONT	oldfont = (HFONT)SelectObject(HDCOwner, font);   

		DrawTextExW( HDCOwner, (wchar_t*)text.c_str(), -1, &clip, DT_CALCRECT | DT_LEFT | DT_TOP| DT_SINGLELINE, 0 );
		RECT r;
		GetClientRect(window, &r);
		Gwen::Renderer::OpenGL::glUV rpos = { (float)clip.left, (float)clip.bottom - ( clip.bottom - clip.top)/3 };
		rpos.u /= scale;
		rpos.v /= scale;
		
		//rpos.v -= 0.5f;
		glRasterPos2f(rpos.u, rpos.v);
		glPushAttrib(GL_LIST_BIT);
		glListBase(base - 32);
		glCallLists(text.length(), GL_UNSIGNED_SHORT, text.c_str());
		glPopAttrib();
		
		SelectObject(HDCOwner, oldfont);			
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
		OpenGL::OpenGL(HDC hdc, HWND _window) : ghdc(hdc), 
			window(_window),
			m_iVertNum(0)
		{
			::FreeImage_Initialise();

			for ( int i=0; i<MaxVerts; i++ )
			{
				m_pVertsLOC[ i ].z = 0.5f;
#if XYZW_ == 3
				m_pVertsLOC[ i ].w = 1.0f;
#endif
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
//			m_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE ); 
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glAlphaFunc(GL_GREATER, 1.0f);
/*
			m_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			m_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
*/
			//m_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
			//m_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
			//m_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

			//m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );
			//m_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );			
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
			if ( m_iVertNum > 0 )
			{
				glVertexPointer(GL_LOC_AXES, GL_FLOAT,  sizeof(glLoc), (const GLvoid *)m_pVertsLOC);
				glEnableClientState(GL_VERTEX_ARRAY);
				glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(DWORD), (const GLvoid*)m_pVertsCOLOR);
				glEnableClientState(GL_COLOR_ARRAY);
				glTexCoordPointer(2, GL_FLOAT, sizeof(glUV), (const GLvoid *)m_pVertsUV);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glDrawArrays(GL_TRIANGLES, 0, (GLsizei) m_iVertNum);

				m_iVertNum = 0;
				glFlush();
			}
		}

		void OpenGL::AddVert( int x, int y )
		{
			if ( m_iVertNum >= MaxVerts-1 )
			{
				Flush();
			}

			m_pVertsLOC[ m_iVertNum ].x = (float)x;
			m_pVertsLOC[ m_iVertNum ].y = (float)y;
			m_pVertsCOLOR[ m_iVertNum ] = m_Color;

			m_iVertNum++;
		}

		void OpenGL::AddVert( int x, int y, float u, float v )
		{
			if ( m_iVertNum >= MaxVerts-1 )
			{
				Flush();
			}

			m_pVertsLOC[ m_iVertNum ].x = -0.5f + (float)x;
			m_pVertsLOC[ m_iVertNum ].y = -0.5f + (float)y;
			m_pVertsUV[ m_iVertNum ].u = u;
			m_pVertsUV[ m_iVertNum ].v = v;

			m_pVertsCOLOR[ m_iVertNum ] = m_Color;

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
			glColor4ubv((GLubyte*)&color);
			m_Color = D3DCOLOR_ARGB( color.a, color.r, color.g, color.b );
		}

		void OpenGL::LoadFont( Gwen::Font* font )
		{
			font->realsize = font->size * Scale();
			font->data = new GLFont(font->facename.c_str(), (int)-font->realsize, this->ghdc, FW_NORMAL);
			/*
			m_FontList.push_back( font );
			// Scale the font according to canvas
			font->realsize = font->size * Scale();

			D3DXFONT_DESC fd;

			memset( &fd, 0, sizeof(fd) );

			wcscpy_s( fd.FaceName, LF_FACESIZE, font->facename.c_str() );

			fd.Width = 0;
			fd.MipLevels = 1;
			fd.CharSet = DEFAULT_CHARSET;
			fd.Height = font->realsize * -1.0f;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.Italic = 0;
			fd.Weight = FW_NORMAL;
			fd.Quality = font->realsize < 14 ? DEFAULT_QUALITY : CLEARTYPE_QUALITY;
			fd.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

			LPD3DXFONT pD3DXFont;
			HRESULT hr = D3DXCreateFontIndirect( m_pDevice, &fd, &pD3DXFont );

			FontData*	pFontData = new FontData();
			pFontData->pFont = pD3DXFont;

			// ID3DXFont doesn't measure trailing spaces, so we measure the width of a space here and store it
			// in the font data - then we can add it to the width when we measure text with trailing spaces.
			{
				RECT rctA = {0,0,0,0};
				pFontData->pFont->DrawTextW( NULL, L"A", -1, &rctA, DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE, 0 );

				RECT rctSpc = {0,0,0,0};
				pFontData->pFont->DrawTextW( NULL, L"A A", -1, &rctSpc, DT_CALCRECT | DT_LEFT | DT_TOP | DT_SINGLELINE, 0 );

				pFontData->iSpaceWidth = rctSpc.right - rctA.right * 2;
			}

			font->data = pFontData;
			*/
		}

		void OpenGL::FreeFont( Gwen::Font* pFont )
		{
			delete (GLFont*)pFont->data;
			pFont->data =0;
			/*
			m_FontList.remove( pFont );

			if ( !pFont->data ) return;

			FontData* pFontData = (FontData*) pFont->data;

			if ( pFontData->pFont )
			{
				pFontData->pFont->Release();
				pFontData->pFont = NULL;
			}

			delete pFontData;
			pFont->data = NULL;
*/
		}

		void OpenGL::RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text )
		{
			Flush();

			if(!pFont->data || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont(pFont);
				LoadFont(pFont);
			}

			if(pFont->data)
			{
				Translate(pos.x, pos.y);
				((GLFont*)pFont->data)->Draw(text, pos, Scale(), window);
			}
			/*;
			// If the font doesn't exist, or the font size should be changed
			if ( !pFont->data || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			FontData* pFontData = (FontData*) pFont->data;
			
			Translate( pos.x, pos.y );

			RECT ClipRect = { pos.x, pos.y, 0, 0 };
			pFontData->pFont->DrawTextW( NULL, text.c_str(), -1, &ClipRect, DT_LEFT | DT_TOP | DT_NOCLIP | DT_SINGLELINE, m_Color );
			*/
		}

		Gwen::Point OpenGL::MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text )
		{
			// If the font doesn't exist, or the font size should be changed
			if ( !pFont->data || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			GLFont* pFontData = (GLFont*) pFont->data;

			Gwen::Point p;
			if(pFontData)
			{
				pFontData->MeasureText(text, p, Scale());
			}

			return p;

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