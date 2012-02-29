#include "Input.h"
#include <Winuser.h>

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

void Input::ClearKeys()
{
	ZeroMemory((void*)&keys,sizeof(Key)*256);

	cursorRelPos.x = 0;
	cursorRelPos.y = 0;
}

void Input::RawKeyInput(RAWKEYBOARD& kb)
{
	if(kb.Message == WM_KEYDOWN)
	{
		if(keys[kb.VKey].down)
		{
			++keys[kb.VKey].repetitions;
			return;
		}

		keys[kb.VKey].down = true;
	}
	if(kb.Message == WM_KEYUP)
	{
		keys[kb.VKey].down = false;
		keys[kb.VKey].repetitions = 0;
	}
}

void Input::RawMouseInput(RAWMOUSE& mouse)
{
	cursorRelPos.x = mouse.lLastX;
	cursorRelPos.y = mouse.lLastY;

	cursorPosition.x+=mouse.lLastX;
	cursorPosition.y+=mouse.lLastY;
}

bool Input::KeyDown(char _keyCode)
{
	return keys[_keyCode].down;
}

bool Input::KeyPressed(char _keyCode)
{
	return keys[_keyCode].down && !keys[_keyCode].repetitions++;
}

POINT Input::GetCursorPosition()
{
	return cursorPosition;
}

POINT Input::GetRelativeCursorPosition()
{
	return cursorRelPos;
}