#pragma once
#include <Windows.h>
#include "EventSystem.h"

class MouseEventHandler
{
	HHOOK HookObject;

	static LRESULT CALLBACK MouseHookCallback( int nCode, WPARAM wParam, LPARAM lParam );

	MouseEventHandler( );

public:

	~MouseEventHandler( );


	static MouseEventHandler* GetSingleton( );


	void Hook( );

	void Unhook( );
};

