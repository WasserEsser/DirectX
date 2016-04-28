#include "Tab.h"
#include "TabControl.h"

Tab::Tab( ) : Parent( nullptr ), TabName( nullptr )
{

}

Tab::Tab( TabControl* Parent, char* TabName ) : Parent( Parent ), TabName( TabName )
{
	Vertex Vertecies[ 4 ]
	{
		{ Parent->GetBoundsXStart( ), Parent->GetBoundsYStart( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) },
		{ Parent->GetBoundsXEnd( ), Parent->GetBoundsYStart( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) },
		{ Parent->GetBoundsXStart( ), Parent->GetBoundsYEnd( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) },
		{ Parent->GetBoundsXEnd( ), Parent->GetBoundsYEnd( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 4 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 4 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );
}

Tab::~Tab( )
{
}

float Tab::GetBoundsXStart( )
{
	return Parent->GetBoundsXStart( );
}

float Tab::GetBoundsYStart( )
{
	return Parent->GetBoundsYStart( );
}

float Tab::GetBoundsXEnd( )
{
	return Parent->GetBoundsXEnd( );
}

float Tab::GetBoundsYEnd( )
{
	return Parent->GetBoundsYEnd( );
}

char* Tab::GetTabName( )
{
	return TabName;
}

void Tab::AddChildren( Renderable* Object )
{
	if ( Object != nullptr )
		Childrens.push_back( Object );
}

void Tab::UpdateVertecies( )
{
	Vertex Vertecies[ 4 ]
	{
		{ Parent->GetBoundsXStart( ), Parent->GetBoundsYStart( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) },
		{ Parent->GetBoundsXEnd( ), Parent->GetBoundsYStart( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) },
		{ Parent->GetBoundsXStart( ), Parent->GetBoundsYEnd( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) },
		{ Parent->GetBoundsXEnd( ), Parent->GetBoundsYEnd( ), 1.f, 1.f, Parent->GetTabBackgroundColor( ) }
	};

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 4 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	for ( auto const &i : Childrens )
	{
		i->UpdateVertecies( );
	}
}

void Tab::RenderObject( )
{
	DirectX::GetSingleton( )->GetDevice( )->SetFVF( FVF );
	DirectX::GetSingleton( )->GetDevice( )->SetStreamSource( 0, VertexBuffer, 0, sizeof( Vertex ) );

	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

	for ( auto const &i : Childrens )
	{
		i->RenderObject( );
	}
}
