#ifndef BASESHADER_H
#define BASESHADER_H

#include <d3d9.h>
#include <d3dx9.h>

#include "Camera.h"

class Mesh;

class BaseShader
{
public:
	static BaseShader* GetInstance();

	void InitShader(LPCSTR _fileName);
	void Render(D3DXMATRIX &_matrix, IDirect3DTexture9 *_texture, Mesh &mesh);
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