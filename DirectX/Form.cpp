#include "Form.h"

Form::Form( )
	: Width( 0.f ), Height( 0.f ), BackgroundColor( 0x0 ), Title( nullptr ), DisplayTitle( false ), TitleBarHeight( 0.f ), TitleColor( 0x0 ), TitleBarColor( 0x0 ), IsBeingDragged( false )
{
}

Form::Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor ) 
	: Width( Width ), Height( Height ), BackgroundColor( BackgroundColor ), Title( nullptr ), DisplayTitle( false ), TitleBarHeight( 0.f ), TitleColor( 0x0 ), TitleBarColor( 0xFFFFFFFF ), IsBeingDragged( false )
{
	this->X = X;
	this->Y = Y;

	Vertex Vertecies[ 9 ] =
	{
		{ X, Y, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y, 1.f, 1.f, BackgroundColor },
		{ X, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 9 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 9 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	EventSystem::GetSingleton( )->AddOnMouseDownEvent( std::bind( &Form::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseUpEvent( std::bind( &Form::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseMoveEvent( std::bind( &Form::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnKeyPressEvent( std::bind( &Form::OnKeyPress, this, std::placeholders::_1 ) );
}

Form::Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, D3DCOLOR TitleColor )
	:  Width( Width ), Height( Height ), BackgroundColor( BackgroundColor ), Title( Title ), DisplayTitle( true ), TitleBarHeight( 25.f ), TitleColor( TitleColor ), TitleBarColor( BackgroundColor ), IsBeingDragged( false )
{
	this->X = X;
	this->Y = Y;

	Vertex Vertecies[ 11 ] =
	{
		{ X, Y, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y, 1.f, 1.f, BackgroundColor },
		{ X, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X, Y + TitleBarHeight, 1.f, 1.f, 0xFFFFFFFF },
		{ X + Width, Y + TitleBarHeight, 1.f, 1.f, 0xFFFFFFFF },
		{ X - 1, Y - 1, 1.f, 1.f, 0xFFFFFFFF },
		{ X - 1, Y + Height, 1.f, 1.f, 0xFFFFFFFF },
		{ X + Width, Y + Height, 1.f, 1.f, 0xFFFFFFFF },
		{ X + Width, Y - 1, 1.f, 1.f, 0xFFFFFFFF },
		{ X - 1, Y - 1, 1.f, 1.f, 0xFFFFFFFF }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 11 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 11 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	EventSystem::GetSingleton( )->AddOnMouseDownEvent( std::bind( &Form::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseUpEvent( std::bind( &Form::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseMoveEvent( std::bind( &Form::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnKeyPressEvent( std::bind( &Form::OnKeyPress, this, std::placeholders::_1 ) );
}

Form::Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, D3DCOLOR TitleColor, D3DCOLOR TitleBarColor )
	: Width( Width ), Height( Height ), BackgroundColor( BackgroundColor ), Title( Title ), DisplayTitle( true ), TitleBarHeight( 25.f ), TitleColor( TitleColor ), TitleBarColor( TitleBarColor ), IsBeingDragged( false )
{
	this->X = X;
	this->Y = Y;

	Vertex Vertecies[ 13 ] =
	{
		{ X, Y, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y, 1.f, 1.f, BackgroundColor },
		{ X, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X, Y, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y, 1.f, 1.f, TitleBarColor },
		{ X, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 13 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 13 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	EventSystem::GetSingleton( )->AddOnMouseDownEvent( std::bind( &Form::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseUpEvent( std::bind( &Form::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseMoveEvent( std::bind( &Form::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnKeyPressEvent( std::bind( &Form::OnKeyPress, this, std::placeholders::_1 ) );
}

Form::Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, float TitleBarHeight, D3DCOLOR TitleColor )
	: Width(  Width ), Height( Height ), BackgroundColor( BackgroundColor ), Title( Title ), DisplayTitle( 1 ), TitleBarHeight( TitleBarHeight ), TitleColor( TitleColor ), TitleBarColor(  ), IsBeingDragged( false )
{
	this->X = X;
	this->Y = Y;

	Vertex Vertecies[ 11 ] =
	{
		{ X, Y, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y, 1.f, 1.f, BackgroundColor },
		{ X, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 11 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 11 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	EventSystem::GetSingleton( )->AddOnMouseDownEvent( std::bind( &Form::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseUpEvent( std::bind( &Form::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseMoveEvent( std::bind( &Form::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnKeyPressEvent( std::bind( &Form::OnKeyPress, this, std::placeholders::_1 ) );
}

Form::Form( float X, float Y, float Width, float Height, D3DCOLOR BackgroundColor, char* Title, float TitleBarHeight, D3DCOLOR TitleColor, D3DCOLOR TitleBarColor )
	: Width( Width ), Height( Height ), BackgroundColor( BackgroundColor ), Title( Title ), DisplayTitle( 1 ), TitleBarHeight( TitleBarHeight ), TitleColor( TitleColor ), TitleBarColor( TitleBarColor ), IsBeingDragged( false )
{
	this->X = X;
	this->Y = Y;

	Vertex Vertecies[ 13 ] =
	{
		{ X, Y, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y, 1.f, 1.f, BackgroundColor },
		{ X, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
		{ X, Y, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y, 1.f, 1.f, TitleBarColor },
		{ X, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y + Height, 1.f, 1.f, TitleBarColor },
		{ X + Width, Y - 1, 1.f, 1.f, TitleBarColor },
		{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 13 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 13 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	EventSystem::GetSingleton( )->AddOnMouseDownEvent( std::bind( &Form::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseUpEvent( std::bind( &Form::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseMoveEvent( std::bind( &Form::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnKeyPressEvent( std::bind( &Form::OnKeyPress, this, std::placeholders::_1 ) );
}

Form::~Form( )
{

}

float Form::GetWidth( ) const
{
	return Width;
}

float Form::GetHeight( ) const
{
	return Height;
}

char* Form::GetTitle( ) const
{
	return Title;
}

bool Form::GetDisplayTitle( ) const
{
	return DisplayTitle;
}

float Form::GetTitleBarHeight( ) const
{
	return TitleBarHeight;
}

D3DCOLOR Form::GetTitleColor( ) const
{
	return TitleColor;
}

D3DCOLOR Form::GetTitleBarColor( ) const
{
	return TitleBarColor;
}

D3DCOLOR Form::GetBackgroundColor( ) const
{
	return BackgroundColor;
}

float Form::GetBoundsXStart( )
{
	return X;
}

float Form::GetBoundsYStart( )
{
	return DisplayTitle ? Y + TitleBarHeight : Y;
}

float Form::GetBoundsXEnd( )
{
	return X + Width;
}

float Form::GetBoundsYEnd( )
{
	return Y + Height;
}

void Form::AddChildObject( Renderable* Object )
{
	if ( Object != nullptr ) 
		Childrens.push_back( Object );
}

void Form::UpdateVertecies( )
{
	if ( DisplayTitle )
	{
		if ( TitleBarColor != BackgroundColor )
		{
			Vertex Vertecies[ 13 ] =
			{
				{ X, Y, 1.f, 1.f, BackgroundColor },
				{ X + Width, Y, 1.f, 1.f, BackgroundColor },
				{ X, Y + Height, 1.f, 1.f, BackgroundColor },
				{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
				{ X, Y, 1.f, 1.f, TitleBarColor },
				{ X + Width, Y, 1.f, 1.f, TitleBarColor },
				{ X, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
				{ X + Width, Y + TitleBarHeight, 1.f, 1.f, TitleBarColor },
				{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor },
				{ X - 1, Y + Height, 1.f, 1.f, TitleBarColor },
				{ X + Width, Y + Height, 1.f, 1.f, TitleBarColor },
				{ X + Width, Y - 1, 1.f, 1.f, TitleBarColor },
				{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor }
			};

			void* VertexPointer;

			VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
			memcpy( VertexPointer, Vertecies, 13 * sizeof( Vertex ) );
			VertexBuffer->Unlock( );
		}
		else
		{
			Vertex Vertecies[ 11 ] =
			{
				{ X, Y, 1.f, 1.f, BackgroundColor },
				{ X + Width, Y, 1.f, 1.f, BackgroundColor },
				{ X, Y + Height, 1.f, 1.f, BackgroundColor },
				{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
				{ X, Y + TitleBarHeight, 1.f, 1.f, 0xFFFFFFFF },
				{ X + Width, Y + TitleBarHeight, 1.f, 1.f, 0xFFFFFFFF },
				{ X - 1, Y - 1, 1.f, 1.f, 0xFFFFFFFF },
				{ X - 1, Y + Height, 1.f, 1.f, 0xFFFFFFFF },
				{ X + Width, Y + Height, 1.f, 1.f, 0xFFFFFFFF },
				{ X + Width, Y - 1, 1.f, 1.f, 0xFFFFFFFF },
				{ X - 1, Y - 1, 1.f, 1.f, 0xFFFFFFFF }
			};

			void* VertexPointer;

			VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
			memcpy( VertexPointer, Vertecies, 11 * sizeof( Vertex ) );
			VertexBuffer->Unlock( );
		}
	}
	else
	{
		Vertex Vertecies[ 9 ] =
		{
			{ X, Y, 1.f, 1.f, BackgroundColor },
			{ X + Width, Y, 1.f, 1.f, BackgroundColor },
			{ X, Y + Height, 1.f, 1.f, BackgroundColor },
			{ X + Width, Y + Height, 1.f, 1.f, BackgroundColor },
			{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor },
			{ X - 1, Y + Height, 1.f, 1.f, TitleBarColor },
			{ X + Width, Y + Height, 1.f, 1.f, TitleBarColor },
			{ X + Width, Y - 1, 1.f, 1.f, TitleBarColor },
			{ X - 1, Y - 1, 1.f, 1.f, TitleBarColor }
		};

		void* VertexPointer;

		VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
		memcpy( VertexPointer, Vertecies, 9 * sizeof( Vertex ) );
		VertexBuffer->Unlock( );
	}

	for ( auto const &i : Childrens )
	{
		i->UpdateVertecies( );
	}
}

void Form::RenderObject( )
{
	if ( Active )
	{
		DirectX::GetSingleton( )->GetDevice( )->SetFVF( FVF );
		DirectX::GetSingleton( )->GetDevice( )->SetStreamSource( 0, VertexBuffer, 0, sizeof( Vertex ) );

		DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

		if ( DisplayTitle )
		{
			if ( TitleBarColor != BackgroundColor )
			{
				DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_TRIANGLESTRIP, 4, 2 );

				DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINESTRIP, 8, 4 );
			}
			else
			{
				DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINELIST, 4, 2 );

				DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINESTRIP, 6, 4 );
			}

			RECT Position{ 0, 0, 0, 0 };
			DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &Position, DT_CALCRECT | DT_NOCLIP, TitleColor );
			Position = { static_cast<int>( X ) + static_cast<int>( Width ) / 2 - Position.right / 2, static_cast<int>( Y ) + static_cast<int>( TitleBarHeight ) / 2 - Position.bottom / 2, 0, 0 };
			DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Title, -1, &Position, DT_LEFT | DT_TOP | DT_NOCLIP, TitleColor );
		}
		else
		{
			DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINESTRIP, 4, 4 );
		}

		for ( auto const &i : Childrens )
		{
			i->RenderObject( );
		}
	}
}

bool Form::OnMouseDown( POINT MousePosition, MouseButton MouseButton )
{
	if ( Active )
	{
		if ( MouseButton == MouseButton::MOUSE_LEFT )
		{
			if ( DisplayTitle )
			{
				if ( MousePosition.x >= X && MousePosition.x <= X + Width && MousePosition.y >= Y && MousePosition.y <= Y + TitleBarHeight )
				{
					IsBeingDragged = true;
					ClickedDeltaPosition = { MousePosition.x - static_cast< int >( X ), MousePosition.y - static_cast< int >( Y ) };
					return true;
				}

				return false;
			}

			if ( MousePosition.x >= X && MousePosition.x <= X + Width && MousePosition.y >= Y && MousePosition.y <= Y + Height )
			{
				IsBeingDragged = true;
				ClickedDeltaPosition = { MousePosition.x - static_cast< int >( X ), MousePosition.y - static_cast< int >( Y ) };
				return true;
			}
		}
	}

	return false;
}

bool Form::OnMouseUp( POINT MousePosition, MouseButton MouseButton )
{
	if ( MouseButton == MouseButton::MOUSE_LEFT )
	{
		if ( IsBeingDragged )
		{
			IsBeingDragged = false;
			ClickedDeltaPosition = { 0, 0 };
			return true;
		}
	}


	return false;	
}

bool Form::OnMouseMove( POINT MousePosition, MouseButton MouseButton )
{
	if ( Active )
	{
		if ( IsBeingDragged )
		{
			if ( DisplayTitle )
			{
				if ( MousePosition.x >= X && MousePosition.x <= X + Width && MousePosition.y >= Y && MousePosition.y <= Y + TitleBarHeight )
				{
					X = MousePosition.x - ClickedDeltaPosition.x;
					Y = MousePosition.y - ClickedDeltaPosition.y;
					UpdateVertecies( );
					
					for ( auto const &i : Childrens )
					{
						i->UpdateVertecies( );
					}

					return true;
				}

				return false;
			}

			if ( MousePosition.x >= X && MousePosition.x <= X + Width && MousePosition.y >= Y && MousePosition.y <= Y + Height )
			{
				X = MousePosition.x - ClickedDeltaPosition.x;
				Y = MousePosition.y - ClickedDeltaPosition.y;
				UpdateVertecies( );

				for ( auto const &i : Childrens )
				{
					i->UpdateVertecies( );
				}

				return true;
			}
		}
	}

	return false;
}

bool Form::OnKeyPress( DWORD Keycode )
{
	if ( Keycode == VK_F7 )
	{
		Active = !Active;
		return true;
	}

	return false;
}