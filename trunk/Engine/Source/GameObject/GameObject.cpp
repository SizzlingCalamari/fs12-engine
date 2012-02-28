#include "GameObject.h"
#include "..\Helper\BaseShader.h"
#include "..\Wrapper\ModelManager.h"
#include "..\Wrapper\TextureManager.h"

GameObject::GameObject()
{
	width		= 100;
	height		= 100;

	angle		= 0.0f;
	
	facingDir	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	position	= D3DXVECTOR3( 0.0f, 0.0f, -100.0f );

	//model = ModelManager::GetInstance()->LoadModel("Resource\\Models\\OBJ\\Primitives\\Box.obj");
	model = ModelManager::GetInstance()->LoadModel("Resource\\Models\\OBJ\\H2.obj");
	//model = ModelManager::GetInstance()->CreateBox();
	texID = TextureManager::GetInstance()->LoadTexture("Resource\\Texture\\Crate.jpg");
}

GameObject::~GameObject()
{

}

void GameObject::Init()
{

}

void GameObject::Render()
{
	D3DXMATRIX matrix;

	angle += 0.002f;

	D3DXMatrixIdentity(&matrix);

	D3DXMatrixRotationY(&matrix, D3DXToRadian(angle));

	BaseShader::GetInstance()->Render(matrix, model);
}

void GameObject::Update(float _dt)
{

}