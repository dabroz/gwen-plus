#include "stdafx.h"

#include "Gwen/Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Input/Windows.h"

#include <gdiplus.h>
#include "Gwen/Renderers/OpenGL.h"

#pragma comment( lib, "winmm.lib" )

#include "gl/glew.h"

HWND CreateGameWindow( void )
{
	WNDCLASS	wc;
	ZeroMemory( &wc, sizeof( wc ) );

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= DefWindowProc;
	wc.hInstance		= GetModuleHandle(NULL);
	wc.lpszClassName	= L"GWENWindow";
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );

	RegisterClass( &wc );

	HWND hWindow = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		wc.lpszClassName,
		L"GWEN - Open GL Sample",
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
		-1,
		-1,
		1000 + 16,
		500 + 38,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL );

	ShowWindow( hWindow, SW_SHOW );
	SetForegroundWindow( hWindow );
	SetFocus( hWindow );

	return hWindow;
}

HWND					g_pHWND = NULL;
HDC						g_glHDC = NULL;
HGLRC					g_glRenderContext = NULL;

void ResetOpenGLProjection();
void CreateOpenGLDeviceContext()
{
	g_glHDC = GetDC(g_pHWND);

	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof( PIXELFORMATDESCRIPTOR );    // just its size
    pfd.nVersion = 1;   // always 1

    pfd.dwFlags = PFD_SUPPORT_OPENGL |  // OpenGL support - not DirectDraw
                  PFD_DOUBLEBUFFER   |  // double buffering support
                  PFD_DRAW_TO_WINDOW;   // draw to the app window, not to a bitmap image

    pfd.iPixelType = PFD_TYPE_RGBA ;    // red, green, blue, alpha for each pixel
    pfd.cColorBits = 24;                // 24 bit == 8 bits for red, 8 for green, 8 for blue.
                                        // This count of color bits EXCLUDES alpha.

    pfd.cDepthBits = 32;                // 32 bits to measure pixel depth.  

	int pixelFormat = ChoosePixelFormat( g_glHDC, &pfd );
    
	if( pixelFormat == 0 )
    {
        FatalAppExit( NULL, TEXT("ChoosePixelFormat() failed!") );
    }    
	SetPixelFormat( g_glHDC, pixelFormat, &pfd );

	g_glRenderContext = wglCreateContext(g_glHDC);
	    
	wglMakeCurrent( g_glHDC, g_glRenderContext );

	ResetOpenGLProjection();
}

void KillOpenGLDeviceContext()
{
	
	// UNmake your rendering context (make it 'uncurrent')
    wglMakeCurrent( NULL, NULL );

    // Delete the rendering context, we no longer need it.
    wglDeleteContext( g_glRenderContext );
}
void ResetOpenGLProjection()
{
	RECT r;
	if(GetClientRect(g_pHWND, &r))
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(r.left, r.right, r.bottom, r.top, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glViewport(0, 0, r.right - r.left, r.bottom - r.top);
		//::glTranslatef(r.right, r.bottom, 0.0f);
	}
}
void ResetOpenGLDevice()
{
	KillOpenGLDeviceContext();
	CreateOpenGLDeviceContext();
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	g_pHWND = CreateGameWindow();

	CreateOpenGLDeviceContext();	

	Gwen::Renderer::OpenGL * pRenderer = new Gwen::Renderer::OpenGL( g_glHDC, g_pHWND );

	//Gwen::Skin::Simple skin;
	Gwen::Skin::TexturedBase skin;
	skin.SetRender( pRenderer );
	skin.Init("DefaultSkin.png");
	//Gwen::Skin::TexturedBase texturedskin;
	//texturedskin.SetRender( pRenderer );
	//texturedskin.Init();


	Gwen::Controls::Canvas* pCanvas = new Gwen::Controls::Canvas( &skin );
	pCanvas->SetSize( 1000, 500 );

	Gwen::Input::Windows GwenInputHelper;
	GwenInputHelper.Initialize( pCanvas );

	UnitTest* pUnit = new UnitTest( pCanvas );
	pUnit->SetPos( 10, 10 );


	RECT ClientRect;
	GetClientRect( g_pHWND, &ClientRect );

	::glClearColor(0.58f, 0.6666f, 0.6666f, 1.0f);
	MSG msg;
	while( true )
	{
		if ( !IsWindowVisible( g_pHWND ) )
			break;

		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			GwenInputHelper.ProcessMessage( msg );

			if ( msg.message == WM_QUIT )
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Main Loop
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			pCanvas->RenderCanvas();


			SwapBuffers(g_glHDC);
		}

		// Check for resizes
		{
			RECT NewRect;
			GetClientRect( g_pHWND, &NewRect );
			if ( NewRect.right != ClientRect.right )
			{

				pRenderer->Release();
				ResetOpenGLDevice();
				ClientRect = NewRect;

				pCanvas->SetScale( (float)(NewRect.right - NewRect.left) / (float) pCanvas->Width() );
			}
		}
	}   

	KillOpenGLDeviceContext();
    // release your window's DC
    ReleaseDC( g_pHWND, g_glHDC );
    #pragma endregion

    // and a cheesy fade exit
    AnimateWindow( g_pHWND, 200, AW_HIDE | AW_BLEND );

    return msg.wParam;

}