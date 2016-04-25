#pragma once
#include <d3dx9.h>

class Renderable
{
protected:
	IDirect3DVertexBuffer9* VertexBuffer;

	float X;
	float Y;	

	bool Active;


	Renderable( );

	~Renderable( );

public:
	float GetXPosition( );
	float GetYPosition( );

	bool GetActive( );

	void SetActive( bool Active );

	virtual float GetBoundsXStart( );
	virtual float GetBoundsYStart( );

	virtual float GetBoundsXEnd( );
	virtual float GetBoundsYEnd( );


	virtual void UpdateVertecies( );
	virtual void RenderObject( );
};