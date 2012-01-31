#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "..\Helper\Mesh.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetTexture(IDirect3DTexture9* _texture) { texture = _texture; }
	
	void Init();
	void Update(float _dt);
	void Render();

private:
	IDirect3DTexture9	*texture;
	float				speed;
	float				width;
	float				height;
	float				angle;

	D3DXVECTOR3			facingDir;
	D3DXVECTOR3			position;

	//Required for drawing
	Mesh				mesh;
};

#endif