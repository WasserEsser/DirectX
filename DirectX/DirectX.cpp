#include "DirectX.h"

DirectX::DirectX( ) : Interface( nullptr ), Device( nullptr ), Verdana( nullptr ), RenderList( 0 )
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

DirectX::~DirectX( )
{
	if ( Interface != nullptr ) Interface->Release( );
	if ( Device != nullptr ) Device->Release( );
	if ( Verdana != nullptr ) Verdana->Release( );
}

void DirectX::InitializeDirectX( HWND* Window )
{
	Interface = Direct3DCreate9( D3D_SDK_VERSION );
	
	D3DPRESENT_PARAMETERS PresentParameters{ 0 };

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