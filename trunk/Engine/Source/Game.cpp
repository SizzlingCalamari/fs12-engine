#include "Game.h"
#include <algorithm>
#include <fstream>
#include "Wrapper\TextureManager.h"
#include "Wrapper\ModelManager.h"
#include "Wrapper\Input.h"
#include "GameObject\GameObject.h"
#include "Wrapper\AudioManager.h"

#ifdef _DEBUG
#include <iostream>
#endif

Game::Game()
{
	D3D = NULL;
	SFXVolume = 1.0f;
	musicVolume = 1.0f;

	isWindowed = true;

	FPSTimeStamp = GetTickCount();
	previousTimeStamp = GetTickCount();

	srand((unsigned int)GetTickCount());
}

Game::~Game()
{

}

Game* Game::GetInstance()
{
	static Game instance;
	return &instance;
}

void Game::Initialize(HWND hwnd, HINSTANCE hInstance, int _windowWidth, int _windowHeight, bool _isWindowed, bool isVSync)
{
	audioManager = AudioManager::GetInstance();
	D3D = Direct3D::GetInstance();
	modelManager = ModelManager::GetInstance();
	textureManager = TextureManager::GetInstance();
	input = Input::GetInstance();

	windowWidth = _windowWidth;
	windowHeight = _windowHeight;

	//XAud->InitXAudioDevice(XAud);
	audioManager->Init();
	audioManager->LoadSound("Resource\\Sounds\\Avicii - Levels.wav");
	D3D->InitD3D(hwnd, windowWidth, windowHeight);

	//XAud->OpenFile(&audioBuffer, "Resource\\Sounds\\Avicii - Levels.wav");

	gameObj = new GameObject();

	FPSTimeStamp = GetTickCount();
	previousTimeStamp = GetTickCount();
	totalElapsedTime = 0.0f;
}

bool Game::Main()
{
	if (Input() == false)
		return false;

	Update();
	input->ClearKeys();

	Render();
	return true;
}

bool Game::Input()
{
	if(input->IsKeyDown('Q'))
		return false;

	if(input->IsKeyDown('P'))
		audioManager->PlaySound(0);

	/*if(input->IsKeyDown('S'))
		audioManager->StopSound();*/

	if(input->IsKeyDown('D'))
		AudioManager::GetInstance()->Shutdown();

	if(input->IsKeyDown('I'))
		AudioManager::GetInstance()->Init();

	return true;
}

void Game::Update()
{
	DWORD startTimeStamp = GetTickCount();
	dt = (float)((startTimeStamp - previousTimeStamp) / 1000.0f);
	previousTimeStamp = startTimeStamp;
	totalElapsedTime += dt;
	audioManager->UpdateFilters(dt);
}

void Game::Render()
{
	D3D->BeginDraw();
	gameObj->Render();
	D3D->EndDraw();
}

void Game::Shutdown()
{		
	if(audioManager)
	{
		audioManager->Shutdown();
		audioManager = NULL;
	}

	if(modelManager)
	{
		modelManager->Shutdown();
		modelManager = NULL;
	}

	if(textureManager)
	{
		textureManager->Shutdown();
		textureManager = NULL;
	}

	if(D3D)
	{
		D3D->Shutdown();
		D3D = NULL;
	}

	delete gameObj;
}

void Game::SetWindowSize( int _windowWidth, int _windowHeight )
{
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

int Game::GetWindowWidth()
{
	return windowWidth;
}

int Game::GetWindowHeight()
{
	return windowHeight;
}