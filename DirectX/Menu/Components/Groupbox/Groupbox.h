#pragma once
#include "../../Renderable/Renderable.h"
#include <vector>

class Groupbox : public Renderable
{
	Renderable* Parent;


	float Width;
	float Height;

	float LineThickness;

	D3DCOLOR LineColor;


	char* Title;

	D3DCOLOR TitleColor;


	std::vector< Renderable* > Childrens;


	Groupbox( );

public:

	Groupbox( Renderable* Parent, float X, float Y, float Width, float Height, float LineThickness, D3DCOLOR LineColor, char* Title, D3DCOLOR TitleColor );


	~Groupbox( );


	float GetBoundsXStart( ) override;

	float GetBoundsYStart( ) override;

	
	float GetBoundsXEnd( ) override;

	float GetBoundsYEnd( ) override;


	float GetWidth( );

	float GetHeight( );


	float GetLineThickness( );

	D3DCOLOR GetLineColor( );


	const char* GetTitleName( );

	D3DCOLOR GetTitleColor( );

	
	void AddChildren( Renderable* Object );


	void UpdateVertecies( ) override;

	void RenderObject( ) override;
};