#ifndef MESH_H
#define MESH_H

#include <d3d9.h>
#include <d3dx9.h>

struct TextureVertex
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

	void InitMesh(float width, float height, float horizontalSubDiv = 0, float verticalSubDiv = 0);
	void Shutdown();

	IDirect3DVertexDeclaration9* GetVertexDeclaration() { return vertexDecl; }
	IDirect3DIndexBuffer9* GetIndexBuffer() { return indexBuffer; }
	IDirect3DVertexBuffer9* GetVertexBuffer() { return vertexBuffer; }

private:
	IDirect3DVertexDeclaration9		*vertexDecl; // move to d3d
	IDirect3DIndexBuffer9			*indexBuffer;	// use 1 and scale... build plane from -1 to 1 and scale.
	IDirect3DVertexBuffer9			*vertexBuffer;
};

#endif