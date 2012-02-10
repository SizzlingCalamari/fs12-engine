#ifndef MESH_H
#define MESH_H

#include <d3d9.h>
#include <d3dx9.h>

struct VertexNormalTexture
{
	D3DXVECTOR3 position;
	D3DXVECTOR3	normal;
	float u,v;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void InitMesh(const VertexNormalTexture *verts, unsigned int _numVerts, D3DPRIMITIVETYPE _primitiveType);
	void InitIndexedMesh(const VertexNormalTexture *verts, int numVerts, const unsigned int *indices, int numIndices);
	
	void DestroyMesh();

	IDirect3DVertexDeclaration9* GetVertexDeclaration() { return vertexDecl; }
	IDirect3DIndexBuffer9* GetIndexBuffer()				{ return indexBuffer; }
	IDirect3DVertexBuffer9* GetVertexBuffer()			{ return vertexBuffer; }
	unsigned int GetNumVerts()							{ return numVerts; }

private:
	IDirect3DVertexDeclaration9		*vertexDecl;
	IDirect3DIndexBuffer9			*indexBuffer;
	IDirect3DVertexBuffer9			*vertexBuffer;

	unsigned int					numVerts;
	D3DPRIMITIVETYPE				primitiveType;

	int								textureID;
};

#endif