#include "Groupbox.h"
#include "DirectX.h"

Groupbox::Groupbox( ) 
	: Parent( nullptr ), Title( nullptr ), TextColor( 0 ), OutlineColor( 0 ), Childrens( )
{
}

Groupbox::Groupbox( Renderable* Parent, float X, float Y, float Width, float Height, char* Title, D3DCOLOR TextColor, D3DCOLOR OutlineColor )
	: Parent( Parent ), Title( Title ), Width( Width ), Height( Height ), TextColor( TextColor ), OutlineColor( OutlineColor ), Childrens( )
{
	this->X = X;
	this->Y = Y;

	RECT TextPos{ 0, 0, 0, 0 };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &TextPos, DT_CALCRECT | DT_NOCLIP, TextColor );

	Vertex Vertecies[ 6 ]
	{
		{ this->Parent->GetBoundsXStart( ) + X + 30.f, this->Parent->GetBoundsYStart( ) + Y + TextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X, this->Parent->GetBoundsYStart( ) + Y + TextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X, this->Parent->GetBoundsYStart( ) + Height + TextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X + Width, this->Parent->GetBoundsYStart( ) + Height + TextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X + Width, this->Parent->GetBoundsYStart( ) + TextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X + 50.f + TextPos.right / 2, this->Parent->GetBoundsYStart( ) + Y + TextPos.bottom / 2, 1.f, 1.f, OutlineColor }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 6 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 6 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );
}

Groupbox::~Groupbox( )
{
}

const Renderable* Groupbox::GetParent( )
{
	return Parent;
}

const char* Groupbox::GetTitle( )
{
	return Title;
}

D3DCOLOR Groupbox::GetTextColor( )
{
	return TextColor;
}

D3DCOLOR Groupbox::GetOutlineColor( )
{
	return OutlineColor;
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
	return Parent->GetBoundsXStart( ) + X + Width;
}

float Groupbox::GetBoundsYEnd( )
{
	return Parent->GetBoundsYStart( ) + Y + Height;
}

void Groupbox::AddChildren( Renderable* Object )
{
	if ( Object != nullptr )
		Childrens.push_back( Object );
}

void Groupbox::UpdateVertecies( )
{
	RECT CalcTextPos{ 0, 0, 0, 0 };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &CalcTextPos, DT_CALCRECT | DT_NOCLIP, TextColor );

	Vertex Vertecies[ 6 ]
	{
		{ this->Parent->GetBoundsXStart( ) + X + 30.f, this->Parent->GetBoundsYStart( ) + Y + CalcTextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X, this->Parent->GetBoundsYStart( ) + Y + CalcTextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X, this->Parent->GetBoundsYStart( ) + Height + CalcTextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X + Width, this->Parent->GetBoundsYStart( ) + Height + CalcTextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X + Width, this->Parent->GetBoundsYStart( ) + CalcTextPos.bottom / 2, 1.f, 1.f, OutlineColor },
		{ this->Parent->GetBoundsXStart( ) + X + 50.f + CalcTextPos.right, this->Parent->GetBoundsYStart( ) + Y + CalcTextPos.bottom / 2, 1.f, 1.f, OutlineColor }
	};

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 6 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	RECT TextPos{ 0, 0, 0, 0 };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &TextPos, DT_CALCRECT | DT_NOCLIP, TextColor );
	TextPos = { static_cast<int>( this->Parent->GetBoundsXStart( ) + X + 40.f ), static_cast<int>( this->Parent->GetBoundsYStart( ) + Y ), 0, 0 };
	DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &TextPos, DT_LEFT | DT_TOP | DT_NOCLIP, TextColor );

	for ( auto const &i : Childrens )
	{
		i->UpdateVertecies( );
	}
}

void Groupbox::RenderObject( )
{
	DirectX::GetSingleton( )->GetDevice( )->SetFVF( FVF );
	DirectX::GetSingleton( )->GetDevice( )->SetStreamSource( 0, VertexBuffer, 0, 6 * sizeof( Vertex ) );

	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINESTRIP, 0, 6 );

	for ( auto const &i : Childrens )
	{
		i->RenderObject( );
	}
}