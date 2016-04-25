#pragma once

typedef unsigned long DWORD;

class KeyboardEvent
{
protected:
	KeyboardEvent( );

	~KeyboardEvent( );

	virtual bool OnKeyPress( DWORD Key );
	virtual bool OnKeyRelease( DWORD Key );	
};
