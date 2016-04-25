#pragma once
#include "Renderable.h"
#include <vector>

class TabControl;

class Tab : public Renderable
{
	TabControl* Parent;

	char* TabName;

	std::vector<Renderable*> Childrens;

	
	Tab( );

public:

	Tab( TabControl* Parent, char* TabName );

	
	~Tab( );


	float GetBoundsXStart( ) override;
	float GetBoundsYStart( ) override;

	float GetBoundsXEnd( ) override;
	float GetBoundsYEnd( ) override;

	char* GetTabName( );


	void AddChildren( Renderable* Object );


	void UpdateVertecies( ) override;

	void RenderObject( ) override;
};
