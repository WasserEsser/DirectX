#pragma once
#include "Renderable.h"
#include <vector>

class Groupbox : public Renderable
{
	Renderable* Parent;

	char* Title;

	float Width;
	float Height;

	D3DCOLOR TextColor;
	D3DCOLOR OutlineColor;

	std::vector<Renderable*> Childrens;


	Groupbox( );

public:

	Groupbox( Renderable* Parent, float X, float Y, float Width, float Height, char* Title, D3DCOLOR TextColor, D3DCOLOR OutlineColor );


	~Groupbox( );


	const Renderable* GetParent( );

	const char* GetTitle( );

	D3DCOLOR GetTextColor( );
	D3DCOLOR GetOutlineColor( );


	float GetBoundsXStart( ) override;
	float GetBoundsYStart( ) override;

	float GetBoundsXEnd( ) override;
	float GetBoundsYEnd( ) override;


	void AddChildren( Renderable* Object );


	void UpdateVertecies( ) override;
	void RenderObject( ) override;
};
