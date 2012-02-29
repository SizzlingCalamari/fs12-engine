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
	//model = ModelManager::GetInstance()->LoadModel("Resource\\Models\\OBJ\\H2.obj");
	model = ModelManager::GetInstance()->CreateBox();
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
	D3DXMATRIX matrix, translate, rotateX, rotateY;

	angle += 0.0001f;

	D3DXMatrixIdentity(&matrix);

	D3DXMatrixTranslation(&translate, 100.0f, 0.0f, 0.0f);
	D3DXMatrixRotationY(&rotateY, angle);
	D3DXMatrixRotationX(&rotateX, angle);

	D3DXMatrixMultiply(&matrix, &matrix, &rotateX);
	D3DXMatrixMultiply(&matrix, &matrix, &rotateY);

	BaseShader::GetInstance()->RenderIndexed(matrix, model, texID);
}

void GameObject::Update(float _dt)
{

}