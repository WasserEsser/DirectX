#pragma once
#include "DirectX.h"
#include "Renderable.h"
#include "EventSystem.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"

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

	
	std::vector<Renderable*> Childrens;


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


	char* GetTitle( ) const;

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