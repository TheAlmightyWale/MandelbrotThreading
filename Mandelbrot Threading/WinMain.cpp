// (c) 2014 Media Design School
//
// File Name	: WinMain.cpp
// Description	: Program entry point and message handling
// Author		: Jarryd Peterson
// Mail			: jarryd.peterson@mediadesign.school.nz
//
//Basics for Work Queue and Thread taken from http://vichargrave.com/multithreaded-work-queue-in-c/
//Mandelbrot creation information taken from http://stackoverflow.com/questions/369438/smooth-spectrum-for-mandelbrot-set-rendering
// and http://linas.org/art-gallery/escape/escape.html


#include <windows.h>

#include"Fractal Drawer.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 600;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Mandelbrot Threader";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.lpszMenuName = NULL;

	RegisterClass(&wc);

	// Create the window.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Mandelbrot Threader",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
		);

	if (hwnd == NULL)
	{
		return 0;
	}

	//Show Window
	ShowWindow(hwnd, nCmdShow);

	//Initialize Fractal drawer

	FractalDrawer frac(hwnd, GetDC(hwnd), WINDOW_HEIGHT, WINDOW_WIDTH);

	// Run the message loop.
	MSG msg = {};
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//Frame execution
			frac.UpdateScreen();
		}

	}

	return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
					   PostQuitMessage(0);
					   return 0;
	}
		break;

	case WM_PAINT:
	{
					 PAINTSTRUCT ps;
					 HDC hdc = BeginPaint(hwnd, &ps);
					 //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
					 //Painting occurs here

					 EndPaint(hwnd, &ps);
	}
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}