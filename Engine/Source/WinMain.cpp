#include <windows.h>
#include <dbghelp.h>
#include <cstdlib>
#include <crtdbg.h>

#pragma comment(lib, "dbghelp.lib")

#include "Game.h"
#include "Wrapper\Input.h"
#include <fstream>
#include <sstream>

using std::fstream;
using std::istringstream;
using std::string;

const char* g_szWINDOW_CLASS_NAME	= "SGDWindowClass";	

const char* g_szWINDOW_TITLE		= "FS12ENGINE";
int	g_nWINDOW_WIDTH			= 800;				
int	g_nWINDOW_HEIGHT		= 600;				

#ifdef _DEBUG
	#include <iostream>
	#pragma comment(linker, "/SUBSYSTEM:Console")
	const BOOL	g_bIS_WINDOWED			= TRUE;
#else
	#pragma comment(linker, "/SUBSYSTEM:Windows")
	const BOOL	g_bIS_WINDOWED			= FALSE;
#endif

void LoadStartupSettings();

//	Handler function that writes out a dump file
LONG WINAPI Handler(_EXCEPTION_POINTERS * exPointers)
{
	HANDLE theFile = CreateFileA("myDumpFile.mdmp", 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (theFile != INVALID_HANDLE_VALUE)
	{
		_MINIDUMP_EXCEPTION_INFORMATION exInfo;
		exInfo.ClientPointers = NULL;
		exInfo.ThreadId = GetCurrentThreadId();
		exInfo.ExceptionPointers = exPointers;
		
		// Write The Minidump
		MiniDumpWriteDump(GetCurrentProcess(),
			GetCurrentProcessId(),
			theFile,
			MiniDumpNormal,
			&exInfo,
			NULL,
			NULL);
		MessageBoxA(0, "myDumpFile.mdmp", "MiniDump was saved",MB_OK);

	}


	return EXCEPTION_EXECUTE_HANDLER;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//	This is the main message handler of the system.
	PAINTSTRUCT	ps;			//	Used in WM_PAINT.
	HDC			hdc;		//	Handle to a device context.

	//	What is the message 
	switch(msg)
	{
		//	To skip ALT pop up menu (system menu)
		case WM_SYSKEYUP:
		case WM_SYSCHAR:
			return(0);
		break;
		
		//	Handle ALT+F4
		case WM_CLOSE:
		{
			// Sends us a WM_DESTROY
			DestroyWindow(hWnd);			
		}
		break;

		case WM_ACTIVATE:
		{
			if (LOWORD(wParam) != WA_INACTIVE)
			{
				//ShowCursor(false);
				// unpause game code here
			}
			else
			{
				// pause game code here
				//ShowCursor(true);
			}
		}
		break;

		case WM_CREATE: 
		{
			RAWINPUTDEVICE Rid[2];
			Rid[0].usUsagePage = 0x01; 
			Rid[0].usUsage = 0x02; 
			Rid[0].dwFlags = RIDEV_DEVNOTIFY;
			Rid[0].hwndTarget = 0;
			Rid[1].usUsagePage = 0x01; 
			Rid[1].usUsage = 0x06; 
			Rid[1].dwFlags = RIDEV_DEVNOTIFY;
			Rid[1].hwndTarget = 0;
			if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE)
			{
				MessageBox(HWND_DESKTOP, "ERROR: Failed to register raw input devices.",
					"Raw Input Error", MB_OK | MB_ICONERROR);
				return -1;
			}

			return(0);
		}
		break;

		case WM_INPUT:
		{
			Game *game = Game::GetInstance();
			RAWINPUT ri;
			UINT dwSize = sizeof(RAWINPUT);

			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &ri, &dwSize, sizeof(RAWINPUTHEADER));
			
			if (ri.header.dwType == RIM_TYPEKEYBOARD)
				Input::GetInstance()->RawKeyInput(ri.data.keyboard);
			else if (ri.header.dwType == RIM_TYPEMOUSE) 
				Input::GetInstance()->RawMouseInput(ri.data.mouse);
		}
		break;

		case WM_PAINT:
		{
			//	Start painting
			hdc = BeginPaint(hWnd,&ps);

			//	End painting
			EndPaint(hWnd,&ps);
			return(0);
		}
		break;

		case WM_DESTROY: 
		{
			//	Kill the application			
			PostQuitMessage(0);
			return(0);
		}
		break;

		default:
		break;
	}

	//	Process any messages that we didn't take care of 
	return (DefWindowProc(hWnd, msg, wParam, lParam));
}

//	Checks to see if the game was already running in another window.
//
//	NOTE:	Don't call this function if your game needs to have more
//			than one instance running on the same computer (i.e. client/server)
BOOL CheckIfAlreadyRunning(void)
{
	//	Find a window of the same window class name and window title
	HWND hWnd = FindWindow(g_szWINDOW_CLASS_NAME, g_szWINDOW_TITLE);

	//	If one was found
	if (hWnd)
	{
		//	If it was minimized
		if (IsIconic(hWnd))
			//	restore it
			ShowWindow(hWnd, SW_RESTORE);

		//	Bring it to the front
		SetForegroundWindow(hWnd);

		return TRUE;
	}

	//	No other copies found running
	return FALSE;
}


BOOL RegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX	winClassEx;	//	This will describe the window class we will create.

	//	First fill in the window class structure
	winClassEx.cbSize			= sizeof(winClassEx);
	winClassEx.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClassEx.lpfnWndProc		= WindowProc;
	winClassEx.cbClsExtra		= 0;
	winClassEx.cbWndExtra		= 0;
	winClassEx.hInstance		= hInstance;
	winClassEx.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winClassEx.hIconSm			= NULL;
	winClassEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
	winClassEx.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClassEx.lpszMenuName		= NULL; 
	winClassEx.lpszClassName	= g_szWINDOW_CLASS_NAME;

	//	Register the window class
	return RegisterClassEx(&winClassEx);
}

//	Creates and sizes the window appropriately depending on if 
//	the application is windowed or full screen.
HWND MakeWindow(HINSTANCE hInstance)
{
	// Setup window style flags
	DWORD dwWindowStyleFlags = WS_VISIBLE;

	if (g_bIS_WINDOWED)
	{
		dwWindowStyleFlags |= WS_OVERLAPPEDWINDOW;
	}
	else
	{
		dwWindowStyleFlags |= WS_POPUP;
		ShowCursor(FALSE);	// Stop showing the mouse cursor
	}

	// Setup the desired client area size
	RECT rWindow;
	rWindow.left	= 0;
	rWindow.top		= 0;
	rWindow.right	= g_nWINDOW_WIDTH;
	rWindow.bottom	= g_nWINDOW_HEIGHT;

	// Get the dimensions of a window that will have a client rect that
	// will really be the resolution we're looking for.
	AdjustWindowRectEx(&rWindow, 
						dwWindowStyleFlags,
						FALSE, 
						WS_EX_APPWINDOW);
	
	// Calculate the width/height of that window's dimensions
	int nWindowWidth	= rWindow.right - rWindow.left;
	int nWindowHeight	= rWindow.bottom - rWindow.top;

	//	Create the window
	return CreateWindowEx(WS_EX_APPWINDOW,											//	Extended Style flags.
						  g_szWINDOW_CLASS_NAME,									//	Window Class Name.
						  g_szWINDOW_TITLE,											//	Title of the Window.
						  dwWindowStyleFlags,										//	Window Style Flags.
						  (GetSystemMetrics(SM_CXSCREEN)/2) - (nWindowWidth/2),		//	Window Start Point (x, y). 
						  (GetSystemMetrics(SM_CYSCREEN)/2) - (nWindowHeight/2),	//		-Does the math to center the window over the desktop.
						  nWindowWidth,												//	Width of Window.
						  nWindowHeight,											//	Height of Window.
						  NULL,														//	Handle to parent window.
						  NULL,														//	Handle to menu.
						  hInstance,												//	Application Instance.
						  NULL);													//	Creation parameters.
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1L);

	MSG		msg;	//	Generic message.
	HWND	hWnd;	//	Main Window Handle.


	//	if in release mode set the exception filter to write out a dump file
#ifndef _DEBUG
	SetUnhandledExceptionFilter(Handler);
#endif
	// Don't let more than one instance of the application exist
	//
	// NOTE:	Comment out the following section of code if your game needs to have more
	//			than one instance running on the same computer (i.e. client/server)
	////////////////////////////////////////////////////////////////////////
	if (!hPrevInstance)
	{
		if (CheckIfAlreadyRunning())
			return FALSE;
	}
	////////////////////////////////////////////////////////////////////////

	LoadStartupSettings();

	//	Register the window class
	if (!RegisterWindowClass(hInstance))
		return 0;

	//	Create the window
	hWnd = MakeWindow(hInstance);

	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	Game* game = Game::GetInstance();
	game->Initialize(hWnd, hInstance, g_nWINDOW_WIDTH, g_nWINDOW_HEIGHT, g_bIS_WINDOWED, false);

	//	Enter main event loop
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			//	Test if this is a quit
			if (msg.message == WM_QUIT)
				break;
		
			//	Translate any accelerator keys
			TranslateMessage(&msg);

			//	Send the message to the window proc
			DispatchMessage(&msg);
		}
		
		if(game->Main() == false)
			break;
	}
	
	game->Shutdown();
	
	//	Unregister the window class
	UnregisterClass(g_szWINDOW_CLASS_NAME, hInstance);

	//	Return to Windows like this.
	return (int)(msg.wParam);
}

int main()
{
	int msg = WinMain(GetModuleHandle(NULL), NULL, GetCommandLine(), SW_SHOWDEFAULT);

	return 0;
}

void LoadStartupSettings()
{
	std::fstream istr("startup.ini", std::ios_base::in);
	if(!istr)
		return;

	char line[256];

	while( istr.getline(line,256) )
	{
		istringstream newLine(line, istringstream::in);

		string firstWord;

		newLine >> firstWord;

		if(firstWord == "width")
			newLine >> g_nWINDOW_WIDTH;
		else if(firstWord == "height")
			newLine >> g_nWINDOW_HEIGHT;
	}
}