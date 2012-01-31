#include "Mesh.h"
#include "..\Wrapper\Direct3D.h"

Mesh::Mesh()
{
	vertexDecl		= NULL;
	indexBuffer		= NULL;
	vertexBuffer	= NULL;
}

Mesh::~Mesh()
{

}

void Mesh::InitMesh(float width, float height, float horizontalSubDiv, float verticalSubDiv)
{
	TextureVertex verts[4];
	verts[0].position = D3DXVECTOR3( -3.0f, 4.0f, 0.0f );
	verts[1].position = D3DXVECTOR3( 3.0f,	4.0f, 0.0f );
	verts[2].position = D3DXVECTOR3( 3.0f,  -4.0f, 0.0f );
	verts[3].position = D3DXVECTOR3( -3.0f, -4.0f, 0.0f );

	verts[0].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	verts[1].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	verts[2].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	verts[3].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	
	WORD indexList[6] =
	{
		0,1,2,
		0,2,3,
	};

	verts[0].u = 1.0f;	verts[0].v = 0.0f;
	verts[1].u = 0.0f;	verts[1].v = 0.0f;
	verts[2].u = 0.0f;	verts[2].v = 1.0f;
	verts[3].u = 1.0f;	verts[3].v = 1.0f;

	Direct3D::GetInstance()->GetDevice()->CreateVertexBuffer(4*sizeof(TextureVertex), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertexBuffer, 0);
	void *buffer;

	vertexBuffer->Lock(0,						// byte to start the lock at
		4*sizeof(TextureVertex),	// size of the lock
		&buffer,							// pointer to VRAM memory
		D3DLOCK_DISCARD);					// D3DLOCK Flags

	memcpy(buffer, verts, 4*sizeof(TextureVertex));
	vertexBuffer->Unlock();

	Direct3D::GetInstance()->GetDevice()->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &indexBuffer, NULL);
	indexBuffer->Lock(0, 6 * sizeof(WORD), &buffer, 0);
	memcpy(buffer, indexList, 6 * sizeof(WORD));
	indexBuffer->Unlock();

	D3DVERTEXELEMENT9 decl[] =
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0, 12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
		{0, 24,D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0},
		D3DDECL_END()
	};

	Direct3D::GetInstance()->GetDevice()->CreateVertexDeclaration(decl, &vertexDecl);
	Direct3D::GetInstance()->GetDevice()->SetVertexDeclaration(vertexDecl);
}

void Mesh::Shutdown()
{
	if(vertexDecl)
	{
		vertexDecl->Release();
		vertexDecl = NULL;
	}

	if(indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = NULL;
	}

	if(vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}
}