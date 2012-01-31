#ifndef GAME_H
#define GAME_H

#include "Wrapper\Direct3D.h"
#include "GameObject\GameObject.h"
#include <vector>

class BaseState;
class TextureManager;
class Input;
class CSGD_FModManager;

struct Profile
{
};

class Game
{
private:
	//Wrappers
	Direct3D*			D3D;
	TextureManager*		textureManager;
	Input*				input;
	GameObject			gameObj;
	CSGD_FModManager*	fmodManager;
	
	std::vector<BaseState*> gameStates;

	//Window info
	int windowWidth;
	int windowHeight;
	bool isWindowed;
	bool isActive;

	//Time variables
	DWORD FPSTimeStamp;
	float dt;
	float gameTime;
	DWORD previousTimeStamp;
	float totalElapsedTime;

	//Options variables
	float SFXVolume;
	float musicVolume;
	Profile profile;

	Game();
	Game(const Game&);
	Game& operator=(const Game&);
	~Game();

	bool Input();
	void Update();
	void Render();
	bool LoadSettings(const char* fileName);

public:
	float GetElapsedTime() {return dt;}
	float GetTotalTime() {return totalElapsedTime;}
	static Game* GetInstance();

	void Initialize(HWND hwnd, HINSTANCE hInstance, int winWidth, int winHeight, bool isWindowed, bool isVSync);

	bool Main();
	void Shutdown();

	void ChangeState(BaseState* newState);
	void PushState(BaseState* newState);
	void PopState();
	void ClearAllStates();

	void SetWindowSize(int _windowWidth, int _windowHeight);
	void SetSFXVolume(float _SFXVolume){ SFXVolume = _SFXVolume; }
	void SetMusicVolume(float _musicVolume){ musicVolume = _musicVolume; }

	int GetWindowWidth();
	int GetWindowHeight();
	float GetSFXVolume(){return SFXVolume;}
	float GetMusicVolume(){return musicVolume;}
};

#endif