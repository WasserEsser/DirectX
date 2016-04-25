﻿#include "TabControl.h"

TabControl::TabControl( ) : Parent( nullptr ), TabControlWidth( 0 ), BackgroundColor( 0 ), Tabs( ), ActiveTab( 0 )
{	
}

TabControl::TabControl( Form* Parent, float TabControlWidth, D3DCOLOR SelectedTabColor ) : Parent( Parent ), TabControlWidth( TabControlWidth ), BackgroundColor( this->Parent->GetBackgroundColor( ) ), SelectedTabColor( SelectedTabColor ), Tabs( ), ActiveTab( 3 )
{
	X = this->Parent->GetBoundsXStart( );
	Y = this->Parent->GetBoundsYStart( );

	Vertex Vertecies[ 14 ]
	{
		{ X, Y, 1.f, 1.f, BackgroundColor },
		{ X + TabControlWidth, Y, 1.f, 1.f, BackgroundColor },
		{ X, Parent->GetBoundsYEnd( ), 1.f, 1.f, BackgroundColor },
		{ X + TabControlWidth, Parent->GetBoundsYEnd( ), 1.f, 1.f, BackgroundColor },
		{ X, Y - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ X + TabControlWidth + 1, Y - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ X, Y + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ X + TabControlWidth + 1, Y + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ X + TabControlWidth, Y - 1, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ X + TabControlWidth, Y - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ X - 1, Y - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ X - 1, Y + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ X + TabControlWidth, Y + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ X + TabControlWidth, Parent->GetBoundsYEnd( ), 1.f, 1.f, Parent->GetTitleBarColor( ) }
	};

	DirectX::GetSingleton( )->GetDevice( )->CreateVertexBuffer( 14 * sizeof( Vertex ), 0, FVF, D3DPOOL_MANAGED, &VertexBuffer, nullptr );

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 14 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	EventSystem::GetSingleton( )->AddOnMouseDownEvent( std::bind( &TabControl::OnMouseDown, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseUpEvent( std::bind( &TabControl::OnMouseUp, this, std::placeholders::_1, std::placeholders::_2 ) );
	EventSystem::GetSingleton( )->AddOnMouseMoveEvent( std::bind( &TabControl::OnMouseMove, this, std::placeholders::_1, std::placeholders::_2 ) );
}

TabControl::~TabControl( )
{
}

void TabControl::AddTab( Tab* Object )
{
	Tabs.push_back( Object );
	Tabs[ 0 ]->SetActive( true );
}

Form* TabControl::GetParent( )
{
	return Parent;
}

float TabControl::GetTabControlWidth( )
{
	return TabControlWidth;
}

float TabControl::GetTabControlHeight( )
{
	return Parent->GetBoundsYEnd( );
}

float TabControl::GetBoundsXStart( )
{
	return Parent->GetBoundsXStart( ) + TabControlWidth + 1;
}

float TabControl::GetBoundsYStart( )
{
	return Parent->GetBoundsYStart( ) + 1;
}

float TabControl::GetBoundsXEnd( )
{
	return Parent->GetBoundsXEnd( );
}

float TabControl::GetBoundsYEnd( )
{
	return Parent->GetBoundsYEnd( );
}

D3DCOLOR TabControl::GetBackgroundColor( )
{
	return BackgroundColor;
}

D3DCOLOR TabControl::GetSelectedTabColor( )
{
	return SelectedTabColor;
}

BYTE TabControl::GetActiveTab( )
{
	return ActiveTab;
}

void TabControl::RenderObject( )
{
	DirectX::GetSingleton( )->GetDevice( )->SetFVF( FVF );
	DirectX::GetSingleton( )->GetDevice( )->SetStreamSource( 0, VertexBuffer, 0, sizeof( Vertex ) );

	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
	
	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_TRIANGLESTRIP, 4, 2 );

	DirectX::GetSingleton( )->GetDevice( )->DrawPrimitive( D3DPT_LINESTRIP, 8, 5 );

	for ( unsigned int i = 0; i < Tabs.size( ); i++ )
	{
		RECT Position{ 0, 0, 0, 0 };
		DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Tabs[i]->GetTabName( ), -1, &Position, DT_CALCRECT | DT_NOCLIP, 0xFFFFFFFF );
		Position = { static_cast<int>( this->Parent->GetBoundsXStart( ) ) + static_cast<int>( TabControlWidth ) / 2 - Position.right / 2, static_cast<int>( this->Parent->GetBoundsYStart( ) ) + 15 * static_cast<int>( i + 1 ) + 35 * static_cast<int>( i ) + 17 - Position.bottom / 2, 0, 0 };
		DirectX::GetSingleton( )->GetVerdana( )->DrawTextA( nullptr, Tabs[i]->GetTabName( ), -1, &Position, DT_LEFT | DT_TOP | DT_NOCLIP, 0xFFFFFFFF );
	}

	for ( auto const &i : Tabs )
	{
		if ( i->GetActive( ) )
			i->RenderObject( );
	}
}

void TabControl::UpdateVertecies( )
{
	Vertex Vertecies[ 14 ]
	{
		{ this->Parent->GetBoundsXStart( ), this->Parent->GetBoundsYStart( ), 1.f, 1.f, BackgroundColor },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth, this->Parent->GetBoundsYStart( ), 1.f, 1.f, BackgroundColor },
		{ this->Parent->GetBoundsXStart( ), Parent->GetBoundsYEnd( ), 1.f, 1.f, BackgroundColor },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth, Parent->GetBoundsYEnd( ), 1.f, 1.f, BackgroundColor },
		{ this->Parent->GetBoundsXStart( ), this->Parent->GetBoundsYStart( ) - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth + 1, this->Parent->GetBoundsYStart( ) - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ this->Parent->GetBoundsXStart( ), this->Parent->GetBoundsYStart( ) + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth + 1, this->Parent->GetBoundsYStart( ) + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, SelectedTabColor },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth, this->Parent->GetBoundsYStart( ) - 1, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth, this->Parent->GetBoundsYStart( ) - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ this->Parent->GetBoundsXStart( ) - 1, this->Parent->GetBoundsYStart( ) - 1 + 35 * ( ActiveTab - 1 ) + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ this->Parent->GetBoundsXStart( ) - 1, this->Parent->GetBoundsYStart( ) + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth, this->Parent->GetBoundsYStart( ) + 35 * ( ActiveTab - 1 ) + 35 + ActiveTab * 15, 1.f, 1.f, Parent->GetTitleBarColor( ) },
		{ this->Parent->GetBoundsXStart( ) + TabControlWidth, Parent->GetBoundsYEnd( ), 1.f, 1.f, Parent->GetTitleBarColor( ) }
	};

	void* VertexPointer;

	VertexBuffer->Lock( 0, 0, &VertexPointer, 0 );
	memcpy( VertexPointer, Vertecies, 14 * sizeof( Vertex ) );
	VertexBuffer->Unlock( );

	for ( auto const &i : Tabs )
	{
		i->UpdateVertecies( );
	}
}

bool TabControl::OnMouseDown( POINT MousePosition, MouseButton Button )
{
	if ( Parent->GetActive( ) )
	{
		for ( unsigned int i = 0; i < Tabs.size( ); i++ )
		{
			if ( MousePosition.x >= this->Parent->GetBoundsXStart( ) && MousePosition.x <= this->Parent->GetBoundsXStart( ) + TabControlWidth && MousePosition.y >= this->Parent->GetBoundsYStart( ) + 15 * ( i + 1 ) + 35 * i && MousePosition.y <= this->Parent->GetBoundsYStart( ) + 15 * ( i + 1 ) + 35 * i + 35 )
			{
				Tabs[ i ]->SetActive( true );
				ActiveTab = i + 1;

				for ( unsigned int j = 0; j < Tabs.size( ); j++ )
				{
					if ( j != i )
						Tabs[ j ]->SetActive( false );
				}
			}
		}

		UpdateVertecies( );

		return true;
	}

	return false;
}

bool TabControl::OnMouseUp( POINT, MouseButton )
{
	return false;
}

bool TabControl::OnMouseMove( POINT, MouseButton )
{
	return false;
}