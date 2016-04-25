#pragma once
#include "Renderable.h"
#include "MouseEvent.h"

class Checkbox : public Renderable, protected MouseEvent
{
	Renderable* Parent;

	float Lenght;

	D3DCOLOR BackgroundColor;
	D3DCOLOR SelectedColor;

	bool* Boolean;


	Checkbox( );

public:

	Checkbox( Renderable* Parent, float X, float Y, float Lenght, D3DCOLOR BackgroundColor, D3DCOLOR SelectedColor, bool* Boolean );

	~Checkbox( );

	const Renderable* GetParent( );

	float GetLenght( );

	D3DCOLOR GetBackgroundColor( );
	D3DCOLOR GetSelectedColor( );

	const bool* GetBoolean( );


	float GetBoundsXStart( ) override;
	float GetBoundsYStart( ) override;

	float GetBoundsXEnd( ) override;
	float GetBoundsYEnd( ) override;


	void UpdateVertecies( ) override;
	void RenderObject( ) override;

	
	bool OnMouseDown( POINT MousePosition, MouseButton MouseButton ) override;
	bool OnMouseUp( POINT MousePosition, MouseButton MouseButton ) override;
	bool OnMouseMove( POINT MousePosition, MouseButton MouseButton ) override;
};
