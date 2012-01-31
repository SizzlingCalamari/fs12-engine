#include "Direct3D.h"

Direct3D::Direct3D()
{
	d3d = NULL;
	d3dDevice = NULL;
}

Direct3D::~Direct3D()
{
}

Direct3D* Direct3D::GetInstance()
{
	static Direct3D instance;
	return &instance;
}

void Direct3D::InitD3D(HWND _windowHandle, int horizontalRes, int verticalRes, bool windowed, bool vsync)
{
	windowHandle = _windowHandle;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);	

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.hDeviceWindow					=		windowHandle;
	d3dpp.Windowed						=		windowed;
	d3dpp.BackBufferWidth				=		horizontalRes;
	d3dpp.BackBufferHeight				=		verticalRes;
	d3dpp.BackBufferCount				=		1;
	d3dpp.BackBufferFormat				=		(windowed) ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8;
	d3dpp.PresentationInterval			=		(vsync) ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.SwapEffect					=		D3DSWAPEFFECT_DISCARD;
	d3dpp.Flags							=		D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dpp.FullScreen_RefreshRateInHz	=		D3DPRESENT_RATE_DEFAULT;

	// add for 3D
	d3dpp.EnableAutoDepthStencil = true;		// depth stencil
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// stencil foramt

	HRESULT test = d3d->CreateDevice(0, D3DDEVTYPE_HAL, windowHandle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3dDevice);
}

void Direct3D::ChangeDisplayMode(int horizontalRes, int verticalRes, bool windowed, bool vsync)
{
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.hDeviceWindow					=		windowHandle;
	d3dpp.Windowed						=		windowed;
	d3dpp.BackBufferWidth				=		horizontalRes;
	d3dpp.BackBufferHeight				=		verticalRes;
	d3dpp.BackBufferCount				=		1;
	d3dpp.BackBufferFormat				=		(windowed) ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8;
	d3dpp.PresentationInterval			=		(vsync) ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.SwapEffect					=		D3DSWAPEFFECT_DISCARD;
	d3dpp.Flags							=		D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dpp.FullScreen_RefreshRateInHz	=		D3DPRESENT_RATE_DEFAULT;
	
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	d3dDevice->Reset(&d3dpp);

	DWORD dwWindowStyleFlags = WS_VISIBLE;

	HWND top;
	if (windowed)
	{
		dwWindowStyleFlags |= WS_OVERLAPPEDWINDOW;
		ShowCursor(TRUE); // show the mouse cursor
		top = HWND_NOTOPMOST;
	}
	else
	{
		dwWindowStyleFlags |= WS_POPUP;
		ShowCursor(FALSE); // hide the mouse cursor
		top = HWND_TOP;
	}

	SetWindowLong(windowHandle, GWL_STYLE, dwWindowStyleFlags);

	//	Set the window to the middle of the screen.
	if (windowed)
	{
		// Setup the desired client area size
		RECT rWindow;
		rWindow.left	= 0;
		rWindow.top		= 0;
		rWindow.right	= horizontalRes;
		rWindow.bottom	= verticalRes;

		// Get the dimensions of a window that will have a client rect that
		// will really be the resolution we're looking for.
		AdjustWindowRectEx(&rWindow, 
							dwWindowStyleFlags,
							FALSE, 
							WS_EX_APPWINDOW);
		
		// Calculate the width/height of that window's dimensions
		int windowWidth		= rWindow.right - rWindow.left;
		int windowHeight	= rWindow.bottom - rWindow.top;

		SetWindowPos(windowHandle, top,	(GetSystemMetrics(SM_CXSCREEN)>>1) - (windowWidth>>1),
										(GetSystemMetrics(SM_CYSCREEN)>>1) - (windowHeight>>1),
										windowWidth, windowHeight, SWP_SHOWWINDOW);
	}
	else
	{

		// Let windows know the window has changed.
		SetWindowPos(windowHandle, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);

	}
}

void Direct3D::BeginDraw()
{
	d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255,0,255), 1.0f, 0);
	d3dDevice->BeginScene();
}

void Direct3D::EndDraw()
{
	d3dDevice->EndScene();
	d3dDevice->Present(0,0,0,0);
}

void Direct3D::Shutdown()
{
	if(d3d)
	{
		d3d->Release();
		d3d = NULL;
	}

	if(d3dDevice)
	{
		d3dDevice->Release();
		d3dDevice = NULL;
	}
}