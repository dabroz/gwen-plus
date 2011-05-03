#include "stdafx.h"

#include "Gwen/Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Input/Windows.h"

#include <gdiplus.h>
#include "Gwen/Renderers/DirectX9.h"

#pragma comment( lib, "d3dxof.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "dxerr.lib" )
#pragma comment( lib, "d3dx9.lib" )

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
		L"GWEN - Direct 3D Sample",
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
LPDIRECT3D9				g_pD3D = NULL;
IDirect3DDevice9*		g_pD3DDevice = NULL;
D3DPRESENT_PARAMETERS	g_D3DParams;

void CreateD3DDevice()
{
	ZeroMemory( &g_D3DParams, sizeof( g_D3DParams ) );

	RECT ClientRect;
	GetClientRect( g_pHWND, &ClientRect );

	g_D3DParams.Windowed = TRUE;
	g_D3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3DParams.BackBufferWidth = ClientRect.right;
	g_D3DParams.BackBufferHeight = ClientRect.bottom;
	g_D3DParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	g_D3DParams.BackBufferFormat = D3DFMT_X8R8G8B8;
	//g_D3DParams.EnableAutoDepthStencil = TRUE;
	//g_D3DParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	g_D3DParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	HRESULT hr = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										g_pHWND,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&g_D3DParams, 
										&g_pD3DDevice );
	if ( FAILED(hr) )
	{
		OutputDebugString( DXGetErrorDescription( hr ) );
		return;
	}
}

void ResetD3DDevice()
{
	g_pD3DDevice->Reset( &g_D3DParams );
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	g_pHWND = CreateGameWindow();

	CreateD3DDevice();	

	Gwen::Renderer::DirectX9* pRenderer = new Gwen::Renderer::DirectX9( g_pD3DDevice );

	//Gwen::Skin::Simple skin;
	Gwen::Skin::TexturedBase skin;
	skin.SetRender( pRenderer );
	skin.Init( "DefaultSkin.png" );
	//Gwen::Skin::TexturedBase texturedskin;
	//texturedskin.SetRender( pRenderer );
	//texturedskin.Init();

	Gwen::Controls::Canvas* pCanvas = new Gwen::Controls::Canvas( &skin );
	pCanvas->SetSize( 1000, 500 );

	UnitTest* pUnit = new UnitTest( pCanvas );
	pUnit->SetPos( 10, 10 );

	Gwen::Input::Windows InputHelper;
	InputHelper.Initialize( pCanvas );

	RECT ClientRect;
	GetClientRect( g_pHWND, &ClientRect );

	MSG msg;
	while( true )
	{
		if ( !IsWindowVisible( g_pHWND ) )
			break;

		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			InputHelper.ProcessMessage( msg );

			if ( msg.message == WM_QUIT )
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Main Loop
			g_pD3DDevice->BeginScene();

				g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 150, 170, 170 ), 1, 0 );

				pCanvas->RenderCanvas();

			g_pD3DDevice->EndScene();
			g_pD3DDevice->Present( NULL, NULL, NULL, NULL );

		}

		// Check for resizes
		{
			RECT NewRect;
			GetClientRect( g_pHWND, &NewRect );
			if ( NewRect.right != ClientRect.right )
			{
				g_D3DParams.BackBufferWidth = NewRect.right;
				g_D3DParams.BackBufferHeight = NewRect.bottom;

				pRenderer->Release();
				ResetD3DDevice();

				ClientRect = NewRect;

				pCanvas->SetScale( (float)g_D3DParams.BackBufferWidth / (float) pCanvas->Width() );
			}
		}
	}

	if ( g_pD3DDevice )
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if ( g_pD3D )
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}