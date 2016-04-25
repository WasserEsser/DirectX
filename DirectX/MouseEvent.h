#pragma once
#include <Windows.h>
#include "EventSystem.h"

class MouseEvent
{
protected:
	MouseEvent( );

	~MouseEvent( );

	virtual bool OnMouseDown( POINT, MouseButton );
	virtual bool OnMouseUp( POINT, MouseButton );
	virtual bool OnMouseMove( POINT, MouseButton );
};