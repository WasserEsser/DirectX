#include "DirectX.h"
#include "Form.h"

DirectX::DirectX( ) : Interface( nullptr ), Device( nullptr ), Verdana( nullptr ), Asenine( nullptr ), Vegur( nullptr ), Neou( nullptr ), RenderList( 0 )
{
}

DirectX* DirectX::GetSingleton( )
{
	static DirectX Singleton;

	return &Singleton;
}

IDirect3DDevice9* DirectX::GetDevice( )
{
	return Device;
}

ID3DXFont* DirectX::GetVerdana( )
{
	return Verdana;
}

ID3DXFont* DirectX::GetAsenine( )
{
	return Asenine;
}

ID3DXFont* DirectX::GetVegur( )
{
	return Vegur;
}

ID3DXFont* DirectX::GetNeou( )
{
	return Neou;
}

DirectX::~DirectX( )
{
	if ( Interface != nullptr ) Interface->Release( );
	if ( Device != nullptr ) Device->Release( );
	if ( Verdana != nullptr ) Verdana->Release( );
	if ( Asenine != nullptr ) Asenine->Release( );
	if ( Vegur != nullptr ) Vegur->Release( );
	if ( Neou != nullptr ) Neou->Release( );
}

void DirectX::InitializeDirectX( HWND* Window )
{
	Interface = Direct3DCreate9( D3D_SDK_VERSION );

	
	D3DPRESENT_PARAMETERS PresentParameters;
	memset( &PresentParameters, 0, sizeof( D3DPRESENT_PARAMETERS ) );

	PresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	PresentParameters.BackBufferWidth = GetSystemMetrics( SM_CXSCREEN );
	PresentParameters.BackBufferHeight = GetSystemMetrics( SM_CYSCREEN );
	PresentParameters.hDeviceWindow = *Window;
	PresentParameters.Windowed = true;
	PresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PresentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	PresentParameters.EnableAutoDepthStencil = true;

	if ( FAILED( Interface->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, *Window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &PresentParameters, &Device ) ) ) MessageBox( nullptr, "Failed to create Direct3D device", "inVincible", MB_OK );

	D3DXCreateFont( Device, 15, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Verdana", &Verdana );
	D3DXCreateFont( Device, 20, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Vegur", &Vegur );
	D3DXCreateFont( Device, 30, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Asenine", &Asenine );
	D3DXCreateFont( Device, 20, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, "Neou", &Neou );
}

void DirectX::RenderFrame( ) const
{
	Device->Clear( 0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.f, 0 );
	Device->BeginScene( );

	for ( auto const &i : RenderList )
	{
		i->RenderObject( );
	}

	Device->EndScene( );
	Device->Present( nullptr, nullptr, nullptr, nullptr );
}

void DirectX::AddRenderObject( Renderable* Object )
{
	if ( Object != nullptr )
		RenderList.push_back( Object );
}