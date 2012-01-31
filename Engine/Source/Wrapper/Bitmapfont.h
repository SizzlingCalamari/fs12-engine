#pragma once

#include <Windows.h>

class BitmapFont
{
public: 
	BitmapFont();
	~BitmapFont();
	void Draw(const char * text, int posX, int posY, float scale, DWORD color);
	void Reset();

private:
	RECT CellAlgorithm(int id);
};