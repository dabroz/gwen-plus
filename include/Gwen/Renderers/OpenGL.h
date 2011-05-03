/*
	GWEN
	Copyright (c) 2009 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"

#define GL_LOC_AXES 3

struct GLFont;

namespace Gwen 
{
	namespace Renderer 
	{

		class OpenGL : public Gwen::Renderer::Base
		{
			public:

#ifdef WIN32
				OpenGL( HDC hdc, HWND window);
#endif
				~OpenGL();

				virtual void Begin();
				virtual void End();
				virtual void Release();

				virtual void SetDrawColor(Gwen::Color color);

				virtual void DrawLine( int x, int y, int a, int b );
				virtual void DrawFilledRect( Gwen::Rect rect );

				virtual void LoadFont( Gwen::Font* pFont );
				virtual void FreeFont( Gwen::Font* pFont );
				virtual void RenderText( Gwen::Font* pFont, Gwen::Point pos, const Gwen::UnicodeString& text );
				virtual Gwen::Point MeasureText( Gwen::Font* pFont, const Gwen::UnicodeString& text );

				void StartClip();
				void EndClip();

				void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f );
				void LoadTexture( Gwen::Texture* pTexture );
				void FreeTexture( Gwen::Texture* pTexture );

				struct glLoc
				{
					float x, y, z
#if GL_LOC_AXES == 4
						,w
#endif
						;
				};
				struct glUV
				{
					float u, v;
				};
			protected:

				void*				m_pCurrentTexture;
				DWORD				m_Color;

				GLFont		*m_DefaultFont;
				void Flush();
				void AddVert( int x, int y );
				void AddVert( int x, int y, float u, float v );

				static const int	MaxVerts = 1024;
				glLoc m_pVertsLOC[MaxVerts];
				glUV m_pVertsUV[MaxVerts];
				DWORD m_pVertsCOLOR[MaxVerts];
				int				m_iVertNum;

				Gwen::Font::List		m_FontList;
#ifdef WIN32
				HDC ghdc;
				HWND window;
#endif

		};

	}
}