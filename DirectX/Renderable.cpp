#include "Renderable.h"

Renderable::Renderable( ) : VertexBuffer( ), X( 0.f ), Y( 0.f ), Active( false )
{
	
}

void Renderable::UpdateVertecies( )
{

}

float Renderable::GetXPosition( )
{
	return X;
}

float Renderable::GetYPosition( )
{
	return Y;
}

bool Renderable::GetActive( )
{
	return Active;
}

void Renderable::SetActive( bool Active )
{
	this->Active = Active;
}

float Renderable::GetBoundsXStart( )
{
	return 0.f;
}

float Renderable::GetBoundsYStart( )
{
	return 0.f;
}

float Renderable::GetBoundsXEnd( )
{
	return 0.f;
}

float Renderable::GetBoundsYEnd( )
{
	return 0.f;
}

Renderable::~Renderable( )
{
	
}

void Renderable::RenderObject( )
{

}