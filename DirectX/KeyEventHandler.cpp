#include "KeyEventHandler.h"
#include "EventSystem.h"

LRESULT KeyEventHandler::KeyboardHookCallback( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode < HC_ACTION ) return CallNextHookEx( GetSingleton( )->HookObject, nCode, wParam, lParam );

	PKBDLLHOOKSTRUCT KeyInfo = reinterpret_cast< PKBDLLHOOKSTRUCT >( lParam );

	if ( wParam == WM_KEYDOWN )
		EventSystem::GetSingleton( )->DispatchKeyPressEvents( KeyInfo->vkCode );

	if ( wParam == WM_KEYUP )
		EventSystem::GetSingleton( )->DispatchKeyReleaseEvents( KeyInfo->vkCode );

	return CallNextHookEx( GetSingleton( )->HookObject, nCode, wParam, lParam );
}

KeyEventHandler::KeyEventHandler( ) 
	: HookObject( nullptr )
{

}

KeyEventHandler::~KeyEventHandler( )
{
	if ( HookObject != nullptr ) Unhook( );
}

KeyEventHandler* KeyEventHandler::GetSingleton( )
{
	static KeyEventHandler Singleton;

	return &Singleton;
}

void KeyEventHandler::Hook( )
{
	HookObject = SetWindowsHookEx( WH_KEYBOARD_LL, KeyboardHookCallback, nullptr, 0 );
}

void KeyEventHandler::Unhook( )
{
	UnhookWindowsHookEx( HookObject );
}