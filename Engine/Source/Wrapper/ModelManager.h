#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <map>
#include <vector>
class Model;

class ModelManager
{
public:
	static ModelManager* GetInstance();
	Model* LoadModel(char* fileName);
	Model* CreateBox();
	void Shutdown();

private:
	ModelManager(){};

	ModelManager(const ModelManager&);
	ModelManager& operator=(const ModelManager&);

	~ModelManager(){};
	
	// holds a string with the filename and an int to index into our texture array
	std::map<char*, int> modelsMap;
	std::vector<Model*> models;

	static Model* box;
};

#endif