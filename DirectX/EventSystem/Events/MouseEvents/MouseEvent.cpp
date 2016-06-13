#include "MouseEvent.h"

MouseEvent::MouseEvent( )
{

}

MouseEvent::~MouseEvent( )
{

}

bool MouseEvent::OnMouseDown( POINT, MouseButton )
{
	return false;
}

bool MouseEvent::OnMouseUp( POINT, MouseButton )
{
	return false;
}

bool MouseEvent::OnMouseMove( POINT, MouseButton )
{
	return false;
}