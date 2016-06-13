#pragma once
#include "../../DirectX/DirectX.h"
#include "../Renderable/Renderable.h"
#include "../../EventSystem/EventSystem.h"
#include "../../EventSystem/Events/KeyboardEvents/KeyboardEvent.h"
#include "../../EventSystem/Events/MouseEvents/MouseEvent.h"

class Form : public Renderable, protected KeyboardEvent, protected MouseEvent
{
	float Width;
	float Height;

	
	D3DCOLOR BackgroundColor;


	char* Title;

	bool DisplayTitle;

	float TitleBarHeight;

	D3DCOLOR TitleColor;
	D3DCOLOR TitleBarColor;
	

	bool IsBeingDragged;

	POINT ClickedDeltaPosition;

		
	std::vector< Renderable* > Childrens;


	Form( );


	bool OnMouseDown( POINT MousePosition, MouseButton MouseButton ) override;

	bool OnMouseUp( POINT MousePosition, MouseButton MouseButton ) override;

	bool OnMouseMove( POINT MousePosition, MouseButton MouseButton ) override;

	bool OnKeyPress( DWORD Keycode ) override;

public:

	Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor );

	Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, D3DCOLOR TitleColor );

	Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, D3DCOLOR TitleColor, D3DCOLOR TitleBarColor );

	Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, float TitleBarHeight, D3DCOLOR TitleColor );

	Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, float TitleBarHeight, D3DCOLOR TitleColor, D3DCOLOR TitleBarColor );


	~Form( );


	float GetWidth( ) const;

	float GetHeight( ) const;


	D3DCOLOR GetBackgroundColor( ) const;


	const char* GetTitle( ) const;


	bool GetDisplayTitle( ) const;


	float GetTitleBarHeight( ) const;


	D3DCOLOR GetTitleColor( ) const;

	D3DCOLOR GetTitleBarColor( ) const;


	void AddChildObject( Renderable* Object );
	

	float GetBoundsXStart( ) override;

	float GetBoundsYStart( ) override;


	float GetBoundsXEnd( ) override;

	float GetBoundsYEnd( ) override;


	void UpdateVertecies( ) override;

	void RenderObject( ) override;
};