#include "Game.h"
#include <algorithm>
#include <fstream>
#include "Wrapper\TextureManager.h"
#include "Wrapper\Input.h"

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
	D3D = Direct3D::GetInstance();
	textureManager = TextureManager::GetInstance();
	input = Input::GetInstance();

	windowWidth = _windowWidth;
	windowHeight = _windowHeight;

	D3D->InitD3D(hwnd, windowWidth, windowHeight);

	gameObj.Init();
	gameObj.SetTexture(textureManager->LoadTexture("Resource\\Texture\\jeep.png"));

	FPSTimeStamp = GetTickCount();
	previousTimeStamp = GetTickCount();
	totalElapsedTime = 0.0f;
}

bool Game::Main()
{
	if (Input() == false)
		return false;

	Update();

	Render();

	return true;
}

bool Game::Input()
{
	if(input->IsKeyDown('Q'))
		return false;

	return true;
}

void Game::Update()
{
	DWORD startTimeStamp = GetTickCount();
	dt = (float)((startTimeStamp - previousTimeStamp) / 1000.0f);
	previousTimeStamp = startTimeStamp;
	totalElapsedTime += dt;
}

void Game::Render()
{
	D3D->BeginDraw();

	gameObj.Render();

	D3D->EndDraw();
}

void Game::Shutdown()
{
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