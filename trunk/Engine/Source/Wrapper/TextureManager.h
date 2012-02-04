#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <vector>

class TextureManager
{
public:
	static TextureManager* GetInstance();
	int LoadTexture(LPCSTR fileName);
	IDirect3DTexture9* GetTexture(int _id);
	void Shutdown();

private:
	TextureManager(){};

	TextureManager(const TextureManager&);
	TextureManager& operator=(const TextureManager&);

	~TextureManager(){};
	
	// holds a string with the filename and an int to index into our texture array
	std::map<LPCSTR, int> imagesMap;
	std::vector<IDirect3DTexture9*> textures;
};

#endif