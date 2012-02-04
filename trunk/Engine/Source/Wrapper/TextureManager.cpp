#include "TextureManager.h"
#include "Direct3D.h"

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

int TextureManager::LoadTexture(LPCSTR fileName)
{
	std::map<LPCSTR, int>::iterator it; 
	
	
	it = imagesMap.find(fileName);

	if (it == imagesMap.end())
	{
	    IDirect3DTexture9* texture;
		D3DXCreateTextureFromFile(Direct3D::GetInstance()->GetDevice(), fileName, &texture);

		imagesMap.insert(std::map<LPCSTR, int>::value_type(fileName, textures.size()));
		textures.push_back(texture);

		return textures.size()-1; 
	}else
		return it->second;

	return NULL;
}

IDirect3DTexture9* TextureManager::GetTexture(int _id)
{
	return textures[_id];
}

void TextureManager::Shutdown()
{
	
	for(unsigned int i = 0; i<textures.size(); ++i)
	{
		if(textures[i])
		{
			textures[i]->Release();
			textures[i] = NULL;
		}
	}

	textures.clear();

	imagesMap.clear();
}