#ifndef MODEL_H
#define MODEL_H

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

using std::vector;

class Mesh;

enum PrimitiveType { PLANE, BOX, SPHERE };

class Model
{
public:
	Model();
	~Model();

	void LoadModel(const char* const filename);
	void LoadObjModel(const char* const filename);

	void CreatePrimitive(PrimitiveType type);

	Mesh* GetMesh(unsigned int i);
	unsigned int GetMeshCount() { return meshVec.size(); }
	void DestroyModel();
private:
	vector<Mesh*>					meshVec;
};

#endif