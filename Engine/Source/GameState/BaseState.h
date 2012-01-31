#pragma once

#include "../Wrapper/Bitmapfont.h"

class BaseState
{
private:
	int musicID;
	int toggleSoundID;
	int confirmSoundID;
	int selection;
	BitmapFont font;

public:
	virtual void Enter(void) = 0;
	virtual bool Input(void) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(void) = 0;
	virtual void Exit(void) = 0;
	virtual ~BaseState()=0 {}
};