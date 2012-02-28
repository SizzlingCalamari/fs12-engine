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

void Mesh::InitMesh(const VertexNormalTexture *_verts, unsigned int _numVerts, D3DPRIMITIVETYPE _primitiveType)
{
	numVerts = _numVerts;
	primitiveType = _primitiveType;

	IDirect3DDevice9 *d3dDev = Direct3D::GetInstance()->GetDevice();

	d3dDev->CreateVertexBuffer(numVerts*sizeof(VertexNormalTexture), 0 ,0 , D3DPOOL_DEFAULT, &vertexBuffer, 0);
	void *buffer;

	vertexBuffer->Lock(0, numVerts*sizeof(VertexNormalTexture), &buffer, 0);

	memcpy(buffer, _verts, numVerts*sizeof(VertexNormalTexture));

	vertexBuffer->Unlock();

	D3DVERTEXELEMENT9 decl[] =
	{
		{0,0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0,12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0,24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	d3dDev->CreateVertexDeclaration(decl, &vertexDecl);

	vertexBuffer->Unlock();
	
}

void Mesh::InitIndexedMesh(const VertexNormalTexture* _verts, int _numVerts, const unsigned int* _indices, int _numIndices)
{
	numVerts = _numVerts;
	primitiveType = D3DPT_TRIANGLELIST;
	numPrimitives = _numIndices/3;

	IDirect3DDevice9 *d3dDev = Direct3D::GetInstance()->GetDevice();

	d3dDev->CreateVertexBuffer(_numVerts*sizeof(VertexNormalTexture), 0, 0, D3DPOOL_DEFAULT, &vertexBuffer, 0);
	void *buffer;

	vertexBuffer->Lock(0, _numVerts*sizeof(VertexNormalTexture), &buffer, 0);

	memcpy(buffer, _verts, _numVerts*sizeof(VertexNormalTexture));

	vertexBuffer->Unlock();

	d3dDev->CreateIndexBuffer(_numIndices * sizeof(unsigned int), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &indexBuffer, 0);
	indexBuffer->Lock(0, _numIndices * sizeof(unsigned int), &buffer, 0);
	memcpy(buffer, _indices, _numIndices * sizeof(unsigned int));
	indexBuffer->Unlock();

	D3DVERTEXELEMENT9 decl[] =
	{
		{0,0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0,12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0,24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	d3dDev->CreateVertexDeclaration(decl, &vertexDecl);
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