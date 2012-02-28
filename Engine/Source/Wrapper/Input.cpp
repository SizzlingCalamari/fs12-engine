#include "Input.h"
#include <Winuser.h>

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

void Input::ClearKeys()
{
	ZeroMemory((void*)&keys,256);

	cursorRelPos.x = 0;
	cursorRelPos.y = 0;
}

void Input::RawKeyInput(RAWKEYBOARD& kb)
{
	if(kb.Message == WM_KEYDOWN)
		keys[kb.VKey] = true;
	if(kb.Message == WM_KEYUP)
		keys[kb.VKey] = false;
}

void Input::RawMouseInput(RAWMOUSE& mouse)
{
	cursorRelPos.x = mouse.lLastX;
	cursorRelPos.y = mouse.lLastY;

	cursorPosition.x+=mouse.lLastX;
	cursorPosition.y+=mouse.lLastY;
}

bool Input::IsKeyDown(char keyCode)
{
	return keys[keyCode];
}

POINT Input::GetCursorPosition()
{
	return cursorPosition;
}

POINT Input::GetRelativeCursorPosition()
{
	return cursorRelPos;
}