#pragma once
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "Renderable.h"

#define FVF ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )

struct Vertex
{
	float X, Y, Z, RHW;
	DWORD Color;
};

class DirectX
{
	IDirect3D9* Interface;
	IDirect3DDevice9* Device;
	ID3DXFont* Verdana;
	ID3DXFont* Vegur;
	ID3DXFont* Asenine;
	ID3DXFont* Neou;
	
	std::vector<Renderable*> RenderList;


	DirectX( );

public:
	
	static DirectX* GetSingleton( );


	~DirectX( );


	IDirect3DDevice9* GetDevice( );


	ID3DXFont* GetVerdana( );

	ID3DXFont* GetAsenine( );

	ID3DXFont* GetVegur( );

	ID3DXFont* GetNeou( );


	void InitializeDirectX( HWND* Window );

	void RenderFrame( ) const;

	void AddRenderObject( Renderable* Object );
};
