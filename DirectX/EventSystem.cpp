﻿#include "EventSystem.h"

EventSystem::EventSystem( ) : OnMouseDown( ), OnMouseUp( ), OnMouseMove( ), OnKeyPress( ), OnKeyRelease( )
{

}

void EventSystem::AddOnMouseDownEvent( std::function<bool( POINT, MouseButton )> Event )
{
	OnMouseDown.push_back( Event );
}

void EventSystem::AddOnMouseUpEvent( std::function<bool( POINT, MouseButton )> Event )
{
	OnMouseUp.push_back( Event );
}

void EventSystem::AddOnMouseMoveEvent( std::function<bool( POINT, MouseButton )> Event )
{
	OnMouseMove.push_back( Event );
}

void EventSystem::AddOnKeyPressEvent( std::function<bool(DWORD)> Event )
{
	OnKeyPress.push_back( Event );
}

void EventSystem::DispatchMouseDownEvents( POINT MousePosition, MouseButton MouseButton )
{
	for ( auto const &i : OnMouseDown )
	{
		if ( i( MousePosition, MouseButton ) ) return;
	}
}

void EventSystem::DispatchMouseUpEvents( POINT MousePosition, MouseButton MouseButton )
{
	for ( auto const &i : OnMouseUp )
	{
		if ( i( MousePosition, MouseButton ) ) return;
	}
}

void EventSystem::DispatchMouseMoveEvents( POINT MousePosition, MouseButton MouseButton )
{
	for ( auto const &i : OnMouseMove )
	{
		if ( i( MousePosition, MouseButton ) ) return;
	}
}

void EventSystem::DispatchKeyPressEvents( DWORD Keycode )
{
	for ( auto const &i : OnKeyPress )
	{
		if ( i( Keycode ) ) return;
	}
}

void EventSystem::DispatchKeyReleaseEvents( DWORD Keycode )
{
	for ( auto const &i : OnKeyRelease )
	{
		if ( i( Keycode ) ) return;
	}
}

void EventSystem::AddOnKeyReleaseEvent( std::function<bool(DWORD)> Event )
{
	OnKeyRelease.push_back( Event );
}

EventSystem::~EventSystem( )
{

}

EventSystem* EventSystem::GetSingleton( )
{
	static EventSystem Singleton;

	return &Singleton;
}