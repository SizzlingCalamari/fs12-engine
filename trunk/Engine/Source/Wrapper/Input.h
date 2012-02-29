#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

struct Key
{
	Key() : down(false), repetitions(0) {};
	bool down;
	unsigned int repetitions;
	// something here to handle events (string, function call, anything)
};

class Input
{
public:

	void ClearKeys();
	void RawKeyInput(RAWKEYBOARD& kb);
	void RawMouseInput(RAWMOUSE& mouse);

	bool KeyDown(char _keyCode);
	bool KeyPressed(char _keyCode);
	POINT GetCursorPosition();
	POINT GetRelativeCursorPosition();

	static Input *GetInstance();

private:
	Input(){};
	~Input(){};
	Input(Input &ref);
	Input &operator=(Input &ref);

	Key keys[256];
	unsigned int startTime;
	unsigned int endTime;

	POINT cursorPosition;
	POINT cursorRelPos;
};

#endif