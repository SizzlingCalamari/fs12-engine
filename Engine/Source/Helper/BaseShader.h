#ifndef BASESHADER_H
#define BASESHADER_H

#include <d3d9.h>
#include <d3dx9.h>

#include "..\Wrapper\TextureManager.h"
#include "Camera.h"

class Model;

class BaseShader
{
public:
	static BaseShader* GetInstance();

	void InitShader(LPCSTR _fileName);
	void Render(D3DXMATRIX& _matrix, Model* model);
	void RenderIndexed(D3DXMATRIX& _matrix, Model* model);
	void Render(D3DXMATRIX& _matrix, Model* model, int textureID);
	void RenderIndexed(D3DXMATRIX &_matrix, Model *model, int textureID);
	void ShutdownShader();

private:
	BaseShader();
	~BaseShader();
	BaseShader(BaseShader &ref);
	BaseShader &operator=(BaseShader &ref);

	CCamera							myCamera; // hold a pointer of the camera and have it in the game
	ID3DXEffect						*effect;
};

#endif