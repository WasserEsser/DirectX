#pragma once
#include <Windows.h>
#include <vector>
#include <functional>

enum class MouseButton
{
	MOUSE_NONE = 0x0,
	MOUSE_MOVE = 0x200,
	MOUSE_LEFT = 0x201,
	MOUSE_RIGHT = 0x204
};

class EventSystem
{
	std::vector< std::function< bool( POINT, MouseButton ) > > OnMouseDown;
	std::vector< std::function< bool( POINT, MouseButton ) > > OnMouseUp;
	std::vector< std::function< bool( POINT, MouseButton ) > > OnMouseMove;
				 			    
	std::vector< std::function< bool( DWORD ) > > OnKeyPress;
	std::vector< std::function< bool( DWORD ) > > OnKeyRelease;


	EventSystem( );

public:

	void AddOnMouseDownEvent( std::function< bool( POINT, MouseButton ) > Event );

	void AddOnMouseUpEvent( std::function< bool( POINT, MouseButton ) > Event );

	void AddOnMouseMoveEvent( std::function< bool( POINT, MouseButton ) > Event );


	void AddOnKeyPressEvent( std::function< bool( DWORD ) > Event );

	void AddOnKeyReleaseEvent( std::function< bool( DWORD ) > Event );


	void DispatchMouseDownEvents( POINT MousePosition, MouseButton MouseButton );

	void DispatchMouseUpEvents( POINT MousePosition, MouseButton MouseButton );

	void DispatchMouseMoveEvents( POINT MousePosition, MouseButton MouseButton );


	void DispatchKeyPressEvents( DWORD Keycode );

	void DispatchKeyReleaseEvents( DWORD Keycode );


	~EventSystem( );


	static EventSystem* GetSingleton( );
};
