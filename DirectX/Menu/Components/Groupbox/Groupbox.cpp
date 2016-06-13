#include "Groupbox.h"
#include "../../../DirectX/DirectX.h"

Groupbox::Groupbox( ) 
	: Renderable( ), Parent( nullptr ), Width( 0.f ), Height( 0.f ), LineThickness( 0.f ), LineColor( 0 ), Title( nullptr ), TitleColor( 0 ), Childrens( )
{

}

Groupbox::Groupbox( Renderable* Parent, float X, float Y, float Width, float Height, float LineThickness, D3DCOLOR LineColor, char* Title, D3DCOLOR TitleColor )
	: Renderable( ), Parent( Parent ), Width( Width ), Height( Height ), LineThickness( LineThickness ), LineColor( LineColor ), Title( Title ), TitleColor( TitleColor ), Childrens( )
{
	this->X = X;
	this->Y = Y;

	RECT TextPosition = RECT{ 0, 0, 0, 0 };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &TextPosition, DT_CALCRECT | DT_NOCLIP, TitleColor );

	Vertex Vertecies[ 6 ]
	{
		{ Parent->GetBoundsXStart( ) + X + Width / 16 - 5.f, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y + Height, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X + Width, Parent->GetBoundsYStart( ) + Y + Height, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X + Width, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X + Width / 16 + TextPosition.right + 5.f, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( std::size( Vertecies ) * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer = nullptr;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, std::size( Vertecies ) * sizeof( Vertex ) );
	VertexBuffer->Unlock( );
}

Groupbox::~Groupbox( )
{

}

float Groupbox::GetBoundsXStart( )
{
	return Parent->GetBoundsXStart( ) + X;
}

float Groupbox::GetBoundsYStart( )
{
	return Parent->GetBoundsYStart( ) + Y;
}

float Groupbox::GetBoundsXEnd( )
{
	return Parent->GetBoundsXEnd( ) + X + Width;
}

float Groupbox::GetBoundsYEnd( )
{
	return Parent->GetBoundsYEnd( ) + Y + Height;
}

float Groupbox::GetWidth( )
{
	return Width;
}

float Groupbox::GetHeight( )
{
	return Height;
}

float Groupbox::GetLineThickness( )
{
	return LineThickness;
}

D3DCOLOR Groupbox::GetLineColor( )
{
	return LineColor;
}

const char* Groupbox::GetTitleName( )
{
	return Title;
}

D3DCOLOR Groupbox::GetTitleColor( )
{
	return TitleColor;
}

void Groupbox::AddChildren( Renderable* Object )
{
	if ( Object != nullptr )
		Childrens.push_back( Object );
}

void Groupbox::UpdateVertecies( )
{
	RECT TextPosition = RECT{ 0, 0, 0, 0 };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &TextPosition, DT_CALCRECT | DT_NOCLIP, TitleColor );

	Vertex Vertecies[ 6 ]
	{
		{ Parent->GetBoundsXStart( ) + X + Width / 16 - 5.f, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y + Height, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X + Width, Parent->GetBoundsYStart( ) + Y + Height, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X + Width, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor },
		{ Parent->GetBoundsXStart( ) + X + Width / 16 + TextPosition.right + 5.f, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, LineColor }
	};

	void* VertexPointer = nullptr;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, std::size( Vertecies ) * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	for( auto const &i : Childrens )
		i->UpdateVertecies( );
}

void Groupbox::RenderObject( )
{
	DirectX::GetSingleton( )->GetDevice( )->SetFVF( FVF );
	DirectX::GetSingleton( )->GetDevice( )->SetStreamSource( 0, VertexBuffer, 0, sizeof( Vertex ) );

	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINESTRIP, 0, 4 );
	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINELIST, 4, 2 );

	RECT TextPosition = RECT{ 0, 0, 0, 0 };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &TextPosition, DT_CALCRECT | DT_NOCLIP, TitleColor );

	TextPosition = { static_cast< int >( Parent->GetBoundsXStart( ) + X + Width / 16 ), static_cast< int >( Parent->GetBoundsYStart( ) + Y ) - TextPosition.bottom / 2, TextPosition.right, TextPosition.bottom };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &TextPosition, DT_LEFT | DT_TOP | DT_NOCLIP, TitleColor );

	for( auto const &i : Childrens )
		i->RenderObject( );
}