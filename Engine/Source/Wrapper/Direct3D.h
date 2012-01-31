#ifndef DIRECT3D_H
#define DIRECT3D_H

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")

class Direct3D
{
public:
	static Direct3D *GetInstance();

	IDirect3DDevice9 *GetDevice() { return d3dDevice; }

	void InitD3D(HWND _windowHandle, int _horizontalRes, int _verticalRes, bool windowed = true, bool vsync = false);
	void ChangeDisplayMode(int horizontalRes, int verticalRes, bool windowed, bool vsync = false);
	void BeginDraw();
	void EndDraw();
	void Shutdown();

protected:
	Direct3D();
	~Direct3D();
	Direct3D(Direct3D &ref);
	Direct3D &operator=(Direct3D &ref);
private:

	IDirect3D9			*d3d;
	IDirect3DDevice9	*d3dDevice;
	HWND				windowHandle;
};

#endif