#include <windows.h>
#include "resource.h"
#include <string>

#define play 1
#define exit 2
#define instructiuni 3

const char g_szClassName[] = "myWindowClass";
HWND playb, exitb, instructiunib, statictext1,img;
HANDLE hBitmap;
HDC         hDC;
PAINTSTRUCT Ps;
HFONT	    font;


void LoadMyImage() {

	hBitmap = LoadImageW(NULL, L"F:\\proiect.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:

		LoadMyImage();

		img = CreateWindowW(L"Static", L"",
			WS_CHILD | WS_VISIBLE | SS_BITMAP,
			0, 100, 800, 600, hwnd, (HMENU)1, NULL, NULL);

		SendMessage(img, STM_SETIMAGE,
			(WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);

		//statictext1= CreateWindow("STATIC", "Welcome     to        Perspico      Solver", WS_CHILD|WS_VISIBLE , 370, 200, 70, 70, hwnd, NULL, NULL,NULL);
		playb = CreateWindowW(L"BUTTON", L"Play", WS_CHILD | WS_BORDER | WS_VISIBLE, 385, 280, 40, 30, hwnd, (HMENU)play, NULL, NULL);
		exitb = CreateWindowW(L"BUTTON", L"Exit", WS_CHILD | WS_BORDER | WS_VISIBLE, 385, 330, 40, 30, hwnd, (HMENU)exit, NULL, NULL);
		//instructiunibutton= CreateWindow("BUTTON", "Instructiuni", WS_CHILD | WS_BORDER|WS_VISIBLE, 365, 370, 80, 30, hwnd, NULL, NULL, NULL); 
		break;
	
	case WM_PAINT:

		hDC = BeginPaint(hwnd, &Ps);

		font = CreateFont(46, 28, 0,200,
			FW_NORMAL, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_ROMAN,
			"Times New Roman");

		SelectObject(hDC, font);
		TextOut(hDC, 0, 0, "Welcome to Perspico Solver", 30);
		DeleteObject(font);

		EndPaint(hwnd, &Ps);
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
	
	       case play:
			instructiunib = CreateWindow("BUTTON", "Instructiuni", WS_CHILD | WS_BORDER | WS_VISIBLE, 700, 650, 80, 30, hwnd, NULL, NULL, NULL);
		   break;
    
	       case exit:
		     DestroyWindow(hwnd);
		   break;

		}
		break;
	
    case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, NULL);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, NULL);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"PERSPICO",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 750,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);


	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;

}
