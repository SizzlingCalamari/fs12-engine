#include "GameObject.h"
#include "..\Helper\BaseShader.h"

GameObject::GameObject()
{
	width		= 100;
	height		= 100;

	angle		= 0.0f;
	
	facingDir	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	position	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}

GameObject::~GameObject()
{

}

void GameObject::Init()
{
	mesh.InitMesh(20,20);
}

void GameObject::Render()
{
	D3DXMATRIX matrix;

	//angle += 0.001;

	D3DXMatrixIdentity(&matrix);

	D3DXMatrixRotationY(&matrix, D3DXToRadian(angle));

	BaseShader::GetInstance()->Render(matrix, texture, mesh);
}

void GameObject::Update(float _dt)
{

}