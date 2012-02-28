#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

class Input
{
public:

	void ClearKeys();
	void RawKeyInput(RAWKEYBOARD& kb);
	void RawMouseInput(RAWMOUSE& mouse);

	bool IsKeyDown(char keyCode);
	POINT GetCursorPosition();
	POINT GetRelativeCursorPosition();

	static Input *GetInstance();

private:
	Input(){};
	~Input(){};
	Input(Input &ref);
	Input &operator=(Input &ref);

	bool keys[256];

	POINT cursorPosition;
	POINT cursorRelPos;
};

#endif