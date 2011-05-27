/*
	GWEN
	Copyright (c) 2009 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/BaseRender.h"

struct GLFont;

namespace Gwen 
{
	namespace Renderer 
	{

		class OpenGL : public Gwen::Renderer::Base
		{
			public:

				struct Vertex
				{
					float x, y, z;
					float u, v;
					unsigned char r, g, b, a;
				};

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

				void StartClip();
				void EndClip();

				void DrawTexturedRect( Gwen::Texture* pTexture, Gwen::Rect pTargetRect, float u1=0.0f, float v1=0.0f, float u2=1.0f, float v2=1.0f );
				void LoadTexture( Gwen::Texture* pTexture );
				void FreeTexture( Gwen::Texture* pTexture );


			protected:

				static const int	MaxVerts = 1024;


				void Flush();
				void AddVert( int x, int y );
				void AddVert( int x, int y, float u, float v );

				Gwen::Color			m_Color;
				int					m_iVertNum;
				Vertex				m_Vertices[ MaxVerts ];

				Gwen::Font::List		m_FontList;
				GLFont				*m_DefaultFont;

#ifdef WIN32
				HDC ghdc;
				HWND window;
#endif

		};

	}
}