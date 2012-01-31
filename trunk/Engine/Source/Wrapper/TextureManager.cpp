#include "TextureManager.h"
#include "Direct3D.h"


TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

IDirect3DTexture9* TextureManager::LoadTexture(LPCSTR fileName)
{
	std::map<LPCSTR, IDirect3DTexture9*>::iterator it; 
	
	
	it = imagesMap.find(fileName);

	if (it == imagesMap.end())
	{
	    IDirect3DTexture9* texture;
		D3DXCreateTextureFromFile(Direct3D::GetInstance()->GetDevice(), fileName, &texture);
		imagesMap.insert(std::map<LPCSTR, IDirect3DTexture9*>::value_type(fileName, texture));

		return texture; 
	}else
		return it->second;

	return NULL;
}

void TextureManager::Shutdown()
{
	std::map<LPCSTR, IDirect3DTexture9*>::iterator it;

	it = imagesMap.begin();

	while(it != imagesMap.end())
	{
		if(it->second)
		{
			it->second->Release();
			it->second = NULL;
		}

		it++;
	}

	imagesMap.clear();
}