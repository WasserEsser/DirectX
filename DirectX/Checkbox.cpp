#include "Checkbox.h"
#include "DirectX.h"

Checkbox::Checkbox( ) : Parent( nullptr ), Lenght( 0 ), BackgroundColor( 0 ), SelectedColor( 0 ), Boolean( nullptr )
{
}

Checkbox::Checkbox( Renderable* Parent, float X, float Y, float Lenght, D3DCOLOR BackgroundColor, D3DCOLOR SelectedColor, bool* Boolean )
	: Parent( Parent ), Lenght( Lenght ), BackgroundColor( BackgroundColor ), SelectedColor( SelectedColor ), Boolean( Boolean )
{
	this->X = X;
	this->Y = Y;

	Vertex Vertecies[ 9 ]
	{
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y + Lenght, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X + Lenght, Parent->GetBoundsYStart( ) + Y + Lenght, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X + Lenght, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X + 1, Parent->GetBoundsYStart( ) + Y + 1, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor },
		{ Parent->GetBoundsXStart( ) + X + 1, Parent->GetBoundsYStart( ) + Y + Lenght - 2, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor },
		{ Parent->GetBoundsXStart( ) + X + Lenght - 2, Parent->GetBoundsYStart( ) + Y + 1, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor },
		{ Parent->GetBoundsXStart( ) + X + Lenght - 2, Parent->GetBoundsYStart( ) + Y + Lenght - 2, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 9 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 9 * sizeof( Vertecies ) );
	VertexBuffer->Unlock( );

	EventSystem::GetSingleton( )->AddOnMouseDownEvent( std::bind( &Checkbox::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseUpEvent( std::bind( &Checkbox::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseMoveEvent( std::bind( &Checkbox::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2 ) );
}

Checkbox::~Checkbox( )
{
}

const Renderable* Checkbox::GetParent( )
{
	return Parent;
}

float Checkbox::GetLenght( )
{
	return Lenght;
}

D3DCOLOR Checkbox::GetBackgroundColor( )
{
	return BackgroundColor;
}

D3DCOLOR Checkbox::GetSelectedColor( )
{
	return SelectedColor;
}

const bool* Checkbox::GetBoolean( )
{
	return Boolean;
}

float Checkbox::GetBoundsXStart( )
{
	return Parent->GetBoundsXStart( ) + X;
}

float Checkbox::GetBoundsYStart( )
{
	return Parent->GetBoundsYStart( ) + Y;
}

float Checkbox::GetBoundsXEnd( )
{
	return Parent->GetBoundsXStart( ) + X + Lenght;
}

float Checkbox::GetBoundsYEnd( )
{
	return Parent->GetBoundsYStart( ) + Y + Lenght;
}

void Checkbox::UpdateVertecies( )
{
	Vertex Vertecies[ 9 ]
	{
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y + Lenght, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X + Lenght, Parent->GetBoundsYStart( ) + Y + Lenght, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X + Lenght, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X, Parent->GetBoundsYStart( ) + Y, 1.f, 1.f, 0xFF000000 },
		{ Parent->GetBoundsXStart( ) + X + 1, Parent->GetBoundsYStart( ) + Y + 1, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor },
		{ Parent->GetBoundsXStart( ) + X + 1, Parent->GetBoundsYStart( ) + Y + Lenght - 2, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor },
		{ Parent->GetBoundsXStart( ) + X + Lenght - 2, Parent->GetBoundsYStart( ) + Y + 1, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor },
		{ Parent->GetBoundsXStart( ) + X + Lenght - 2, Parent->GetBoundsYStart( ) + Y + Lenght - 2, 1.f, 1.f, *Boolean ? SelectedColor : BackgroundColor }
	};

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 9 * sizeof( Vertecies ) );
	VertexBuffer->Unlock( );
}

void Checkbox::RenderObject( )
{
	DirectX::GetSingleton( )->GetDevice( )->SetFVF( FVF );
	DirectX::GetSingleton( )->GetDevice( )->SetStreamSource( 0, VertexBuffer, 0, sizeof( Vertex ) );

	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINESTRIP, 0, 5 );
	
	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_TRIANGLESTRIP, 5, 2 );
}

bool Checkbox::OnMouseDown( POINT MousePosition, MouseButton MouseButton )
{
	if ( MouseButton == MouseButton::MOUSE_LEFT )
	{
		if ( MousePosition.x >= GetBoundsXStart( ) && MousePosition.x <= GetBoundsXEnd( ) && MousePosition.y >= GetBoundsYStart( ) && MousePosition.y <= GetBoundsYEnd( ) )
		{
			*Boolean = !*Boolean;

			return true;
		}
	}

	return false;
}

bool Checkbox::OnMouseUp( POINT MousePosition, MouseButton MouseButton )
{
	return false;
}

bool Checkbox::OnMouseMove( POINT MousePosition, MouseButton MouseButton )
{
	return false;
}