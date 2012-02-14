#ifndef GAME_H
#define GAME_H


#include <vector>
#include "Wrapper\Direct3D.h"

class BaseState;
class TextureManager;
class Input;
class CSGD_FModManager;
class ModelManager;
class GameObject;
class AudioManager;

struct Profile
{
};

class Game
{
private:
	//Wrappers
	Direct3D*			D3D;
	AudioManager*		audioManager;
	ModelManager*		modelManager;
	TextureManager*		textureManager;
	Input*				input;
	
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

	//Testing variables (delete later on)
	GameObject *gameObj;

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