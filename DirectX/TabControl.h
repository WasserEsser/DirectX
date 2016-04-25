#pragma once
#include "EventSystem.h"
#include "DirectX.h"
#include "Form.h"
#include "MouseEvent.h"
#include "Tab.h"

class TabControl : public Renderable, protected MouseEvent
{
	Form* Parent;	

	float TabControlWidth;

	D3DCOLOR BackgroundColor;
	D3DCOLOR SelectedTabColor;
		

	std::vector<Tab*> Tabs;

	
	BYTE ActiveTab;


	TabControl( );

public:
	
	TabControl( Form* Parent, float TabControlWidth, D3DCOLOR SelectedTabColor );


	~TabControl( );


	void AddTab( Tab* Object );


	Form* GetParent( );

	float GetTabControlWidth( );
	float GetTabControlHeight( );
	
	float GetBoundsXStart( ) override;
	float GetBoundsYStart( ) override;

	float GetBoundsXEnd( ) override;
	float GetBoundsYEnd( ) override;

	D3DCOLOR GetBackgroundColor( );
	D3DCOLOR GetSelectedTabColor( );


	BYTE GetActiveTab( );

	
	void RenderObject( ) override;

	void UpdateVertecies( ) override;


	bool OnMouseDown( POINT MousePosition, MouseButton Button ) override;
	bool OnMouseUp( POINT, MouseButton ) override;
	bool OnMouseMove( POINT, MouseButton ) override;
};