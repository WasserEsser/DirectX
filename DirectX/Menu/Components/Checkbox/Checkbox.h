#pragma once
#include "Menu/Renderable/Renderable.h"
#include "EventSystem/Events/MouseEvents/MouseEvent.h"
#include "EventSystem/EventSystem.h"

class Checkbox : public Renderable, protected MouseEvent
{
	Renderable*	Parent;

	float Length;

	D3DCOLOR OutlineColor;
	D3DCOLOR EnabledColor;

	
	bool* Representive;

	
	Checkbox( );

public:

	Checkbox( Renderable* Parent, float Lenght, D3DCOLOR OutlineColor, D3DCOLOR EnabledColor, bool* Representive );


	~Checkbox( );


	const Renderable* GetParent( );

	const bool* GetRepresentive( );


	float GetLength( );


	D3DCOLOR GetOutlineColor( );

	D3DCOLOR GetEnabledColor( );


	float GetBoundsXStart( ) override;

	float GetBoundsYStart( ) override;


	float GetBoundsXEnd( ) override;

	float GetBoundsYEnd( ) override;


	void RenderObject( ) override;

	void UpdateVertecies( ) override;


	bool OnMouseDown( POINT, MouseButton ) override;

	bool OnMouseUp( POINT, MouseButton ) override;

	bool OnMouseMove( POINT, MouseButton ) override;
};