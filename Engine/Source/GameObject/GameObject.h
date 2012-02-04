#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "..\Helper\Mesh.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetTextureID(int _textureID) { textureID = _textureID; }
	
	void Init();
	void Update(float _dt);
	void Render();

private:
	float				speed;
	float				width;
	float				height;
	float				angle;

	D3DXVECTOR3			facingDir;
	D3DXVECTOR3			position;

	//Required for drawing
	Mesh				mesh;
	int					textureID;
};

#endif