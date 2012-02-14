#include "ModelManager.h"
#include "..\Helper\Model.h"

ModelManager* ModelManager::GetInstance()
{
	static ModelManager instance;
	return &instance;
}

Model* ModelManager::LoadModel(char* fileName)
{
	std::map<char*, int>::iterator it;
	
	it = modelsMap.find(fileName);

	if (it == modelsMap.end())
	{
	    Model* model = new Model();

#ifdef _DEBUG
		// for debugging purposes I'll let you load obj's and other trashy formats =)
		unsigned int count = 0;
		while(true)
		{
			if(fileName[count] == '.')
			{
				count++;
				break;
			}
			count++;
		}

		if(!strcmp(fileName+count, "obj"))
			model->LoadObjModel(fileName);
#else
		// not here though
		model->LoadModel();
#endif
		modelsMap.insert(std::map<char*, int>::value_type(fileName, models.size()));
		models.push_back(model);

		return model; 
	}else
		return models[it->second];

	return NULL;
}

void ModelManager::Shutdown()
{
	
	for(unsigned int i = 0; i<models.size(); ++i)
	{
		models[i]->DestroyModel();
		delete models[i];
		models[i] = NULL;
	}

	models.clear();

	modelsMap.clear();
}