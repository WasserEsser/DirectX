#include "EventSystem.h"

LRESULT CALLBACK EventSystem::MouseHook( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode >= HC_ACTION ) 
	{
		MSLLHOOKSTRUCT* Message = reinterpret_cast< MSLLHOOKSTRUCT* >( lParam );

		switch( wParam )
		{
			case WM_LBUTTONDOWN:
				GetSingleton( )->DispatchMouseDownEvents( Message->pt, MouseButton::MOUSE_LEFT );
				break;
			case WM_MBUTTONDOWN:
				GetSingleton( )->DispatchMouseDownEvents( Message->pt, MouseButton::MOUSE_MIDDLE );
				break;
			case WM_RBUTTONDOWN:
				GetSingleton( )->DispatchMouseDownEvents( Message->pt, MouseButton::MOUSE_RIGHT );
				break;
			case WM_LBUTTONUP:
				GetSingleton( )->DispatchMouseUpEvents( Message->pt, MouseButton::MOUSE_LEFT );
				break;
			case WM_MBUTTONUP:
				GetSingleton( )->DispatchMouseUpEvents( Message->pt, MouseButton::MOUSE_MIDDLE );
				break;
			case WM_RBUTTONUP:
				GetSingleton( )->DispatchMouseUpEvents( Message->pt, MouseButton::MOUSE_RIGHT );
				break;
			case WM_MOUSEMOVE:
				GetSingleton( )->DispatchMouseMoveEvents( Message->pt, MouseButton::MOUSE_NONE ); // TODO: Add button states to callback
				break;
			default:
				break;
		}
	}

	return CallNextHookEx( GetSingleton( )->MouseHookObject, nCode, wParam, lParam );
}

LRESULT CALLBACK EventSystem::KeyboardHook( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode >= HC_ACTION )
	{
		KBDLLHOOKSTRUCT* Message = reinterpret_cast< KBDLLHOOKSTRUCT* >( lParam );

		switch ( wParam )
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				GetSingleton( )->DispatchKeyPressEvents( Message->vkCode );
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				GetSingleton( )->DispatchKeyReleaseEvents( Message->vkCode );
				break;
			default:
				break;
		}
	}

	return CallNextHookEx( GetSingleton( )->KeyboardHookObject, nCode, wParam, lParam );
}

EventSystem::EventSystem( ) 
	: OnMouseDown( ), OnMouseUp( ), OnMouseMove( ), OnKeyPress( ), OnKeyRelease( ), MouseHookObject( nullptr ), KeyboardHookObject( nullptr )
{
	Hook( );
}

void EventSystem::AddOnMouseDownEvent( std::function< bool( POINT, MouseButton ) > Event )
{
	if ( Event != nullptr )
		OnMouseDown.push_back( Event );
}

void EventSystem::AddOnMouseUpEvent( std::function< bool( POINT, MouseButton ) > Event )
{
	if ( Event != nullptr )
		OnMouseUp.push_back( Event );
}

void EventSystem::AddOnMouseMoveEvent( std::function< bool( POINT, MouseButton ) > Event )
{
	if ( Event != nullptr )
		OnMouseMove.push_back( Event );
}

void EventSystem::AddOnKeyPressEvent( std::function< bool( DWORD ) > Event )
{
	if ( Event != nullptr )
		OnKeyPress.push_back( Event );
}

void EventSystem::AddOnKeyReleaseEvent( std::function< bool( DWORD ) > Event )
{
	if ( Event != nullptr )
		OnKeyRelease.push_back( Event );
}

void EventSystem::DispatchMouseDownEvents( POINT MousePosition, MouseButton MouseButton )
{
	for ( auto const &i : OnMouseDown )
		if ( i( MousePosition, MouseButton ) ) return;
}

void EventSystem::DispatchMouseUpEvents( POINT MousePosition, MouseButton MouseButton )
{
	for ( auto const &i : OnMouseUp )
		if ( i( MousePosition, MouseButton ) ) return;
}

void EventSystem::DispatchMouseMoveEvents( POINT MousePosition, MouseButton MouseButton )
{
	for ( auto const &i : OnMouseMove )
		if ( i( MousePosition, MouseButton ) ) return;
}

void EventSystem::DispatchKeyPressEvents( DWORD Keycode )
{
	for ( auto const &i : OnKeyPress )
			if ( i( Keycode ) ) return;
}

void EventSystem::DispatchKeyReleaseEvents( DWORD Keycode )
{
	for ( auto const &i : OnKeyRelease )
			if ( i( Keycode ) ) return;
}

EventSystem::~EventSystem( )
{
	if ( MouseHookObject != nullptr || KeyboardHookObject != nullptr ) Unhook( );
}

EventSystem* EventSystem::GetSingleton( )
{
	static EventSystem Singleton;

	return &Singleton;
}

void EventSystem::Hook( )
{
	MouseHookObject = SetWindowsHookEx( WH_MOUSE_LL, MouseHook, nullptr, 0 );
	KeyboardHookObject = SetWindowsHookEx( WH_KEYBOARD_LL, KeyboardHook, nullptr, 0 );
}

void EventSystem::Unhook( )
{
	UnhookWindowsHookEx( MouseHookObject );
	UnhookWindowsHookEx( KeyboardHookObject );
}