#pragma once
#include <Windows.h>
#include "EventSystem.h"

class KeyEventHandler
{
	HHOOK HookObject;

	static LRESULT CALLBACK KeyboardHookCallback( int nCode, WPARAM wParam, LPARAM lParam );
	
	KeyEventHandler( );

public:
	
	~KeyEventHandler( );


	static KeyEventHandler* GetSingleton( );


	void Hook( );

	void Unhook( );
};
