#include "smk.h"

HWND SMK_CreateDummyWindow(HINSTANCE hInstance, LPWSTR title)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"WndClass";

	RegisterClass(&wc);
	
	return CreateWindow(L"WndClass", L"SteamKeys", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 110, 110, 0, 0, hInstance, 0);
}

void SMK_MessageLoop(void)
{
	MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}