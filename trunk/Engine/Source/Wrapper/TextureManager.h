#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <map>

class TextureManager
{
public:
	static TextureManager* GetInstance();
	IDirect3DTexture9* LoadTexture(LPCSTR fileName);
	void Shutdown();

private:
	TextureManager(){};

	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

	~TextureManager(){};

	std::map<LPCSTR, IDirect3DTexture9*> imagesMap;
};

#endif