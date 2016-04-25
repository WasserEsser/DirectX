#include "MouseEventHandler.h"

LRESULT MouseEventHandler::MouseHookCallback( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode < HC_ACTION ) return CallNextHookEx( GetSingleton( )->HookObject, nCode, wParam, lParam );

	PMSLLHOOKSTRUCT MouseInfo = reinterpret_cast< PMSLLHOOKSTRUCT >( lParam );

	if ( wParam == WM_LBUTTONDOWN ) EventSystem::GetSingleton( )->DispatchMouseDownEvents( MouseInfo->pt, MouseButton::MOUSE_LEFT );

	else if ( wParam == WM_LBUTTONUP ) EventSystem::GetSingleton( )->DispatchMouseUpEvents( MouseInfo->pt, MouseButton::MOUSE_LEFT );

	else if ( wParam == WM_RBUTTONDOWN ) EventSystem::GetSingleton( )->DispatchMouseDownEvents( MouseInfo->pt, MouseButton::MOUSE_RIGHT );

	else if ( wParam == WM_RBUTTONUP ) EventSystem::GetSingleton( )->DispatchMouseUpEvents( MouseInfo->pt, MouseButton::MOUSE_RIGHT );

	else if ( wParam == WM_MOUSEMOVE ) EventSystem::GetSingleton( )->DispatchMouseMoveEvents( MouseInfo->pt, MouseButton::MOUSE_NONE );

	return CallNextHookEx( GetSingleton( )->HookObject, nCode, wParam, lParam );
}

MouseEventHandler::MouseEventHandler( ) : HookObject( )
{

}

MouseEventHandler::~MouseEventHandler( )
{

}

MouseEventHandler* MouseEventHandler::GetSingleton( )
{
	static MouseEventHandler Singleton;

	return &Singleton;
}

void MouseEventHandler::Hook( )
{
	HookObject = SetWindowsHookEx( WH_MOUSE_LL, MouseHookCallback, nullptr, 0 );
}

void MouseEventHandler::Unhook( )
{
	UnhookWindowsHookEx( HookObject );
}