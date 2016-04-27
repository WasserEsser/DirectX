#include "DirectX.h"
#include "Form.h"
#include "Dwmapi.h"
#include "KeyEventHandler.h"
#include "MouseEventHandler.h"
#include "TabControl.h"
#include "Groupbox.h"
#include "Checkbox.h"

bool a = false;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
		case WM_DESTROY:
			PostQuitMessage( 0 );
	}

	return DefWindowProc( hwnd, msg, wParam, lParam );
}

int WINAPI WinMain( HINSTANCE Instance, HINSTANCE PreviousInstance, char* lpCmdLine, int iCmdShow )
{
	auto WindowClass = WNDCLASSEX( );
	memset( &WindowClass, 0, sizeof( WNDCLASSEX ) );

	WindowClass.cbSize = sizeof( WNDCLASSEX );
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.hInstance = Instance;
	WindowClass.hCursor = LoadCursor( nullptr, IDC_ARROW );
	WindowClass.hbrBackground = static_cast< HBRUSH >( CreateSolidBrush( RGB( 0, 0, 0 ) ) );
	WindowClass.lpszClassName = "inVincibleClass";

	RegisterClassEx( &WindowClass );

	auto Window = CreateWindowEx( WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, "inVincibleClass", "inVincible", WS_POPUP, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), nullptr, nullptr, Instance, nullptr );
	SetLayeredWindowAttributes( Window, D3DCOLOR_XRGB( 0, 0, 0 ), 255, ULW_COLORKEY | LWA_ALPHA );

	UpdateWindow( Window );
	ShowWindow( Window, SW_SHOW );

	auto App = DirectX::GetSingleton( );

	App->InitializeDirectX( &Window );
	
	Form Menu = Form( 350, 200, 700, 450, D3DCOLOR_ARGB( 255, 25, 33, 35 ), "inVincible", 30.f, D3DCOLOR_ARGB( 255, 35, 43, 45 ), D3DCOLOR_ARGB( 255, 229, 101, 38 ) );
	App->AddRenderObject( &Menu );

	TabControl TabCtrl = TabControl( &Menu, 150.f, D3DCOLOR_ARGB( 255, 35, 43, 45 ) );
	Menu.AddChildObject( &TabCtrl );

	Tab Tab1 = Tab( &TabCtrl, "LOL" );
	TabCtrl.AddTab( &Tab1 );

	Tab Tab2 = Tab( &TabCtrl, "ROFL" );
	TabCtrl.AddTab( &Tab2 );

	Tab Tab3 = Tab( &TabCtrl, "XD" );
	TabCtrl.AddTab( &Tab3 );

	Tab Tab4 = Tab( &TabCtrl, "LMAO" );
	TabCtrl.AddTab( &Tab4 );

	Tab Tab5 = Tab( &TabCtrl, "HUEHUEHUE" );
	TabCtrl.AddTab( &Tab5 );

	auto MessageQueue = MSG( );

	KeyEventHandler::GetSingleton( )->Hook( );
	MouseEventHandler::GetSingleton( )->Hook( );

	while ( 1 )
	{
		SetWindowPos( Window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

		if ( PeekMessage( &MessageQueue, nullptr, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &MessageQueue );

			DispatchMessage( &MessageQueue );
		}

		if ( MessageQueue.message == WM_QUIT ) break;

		App->RenderFrame( );

		MARGINS Margin{ 0, 0, 1920, 1080 };
		DwmExtendFrameIntoClientArea( Window, &Margin );
	}

	KeyEventHandler::GetSingleton( )->Unhook( );
	MouseEventHandler::GetSingleton( )->Unhook( );

	return EXIT_SUCCESS;
}