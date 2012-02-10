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

void Mesh::InitMesh(const VertexNormalTexture *verts, unsigned int _numVerts, D3DPRIMITIVETYPE _primitiveType)
{
	numVerts = _numVerts;
	primitiveType = _primitiveType;

	IDirect3DDevice9 *d3dDev = Direct3D::GetInstance()->GetDevice();

	d3dDev->CreateVertexBuffer(numVerts*sizeof(VertexNormalTexture), 0 ,0 , D3DPOOL_DEFAULT, &vertexBuffer, 0);
	void *buffer;

	vertexBuffer->Lock(0, numVerts*sizeof(VertexNormalTexture), &buffer, 0);

	memcpy(buffer, verts, numVerts*sizeof(VertexNormalTexture));

	D3DVERTEXELEMENT9 decl[] =
	{
		{0,0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0,0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0,0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	d3dDev->CreateVertexDeclaration(decl, &vertexDecl);

	vertexBuffer->Unlock();
	
}

void Mesh::InitIndexedMesh(const VertexNormalTexture *verts, int numVerts, const unsigned int *indices, int numIndices)
{
	
}

void Mesh::DestroyMesh()
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