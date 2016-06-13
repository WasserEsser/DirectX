#pragma once
#include <Windows.h>

class KeyboardEvent
{
protected:
	KeyboardEvent( );


	~KeyboardEvent( );


	virtual bool OnKeyPress( DWORD Key );

	virtual bool OnKeyRelease( DWORD Key );	
};
