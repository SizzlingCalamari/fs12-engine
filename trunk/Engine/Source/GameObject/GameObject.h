#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "..\Helper\Model.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	
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
	Model*				model;
	
	//only for testing, remove later
	int					texID;
};

#endif