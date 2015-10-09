#include "smk.h"

LRESULT WINAPI SMK_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_HOTKEY)
	{
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

HWND SMK_CreateDummyWindow(HINSTANCE hInstance, LPWSTR title)
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));
	wc.lpfnWndProc = SMK_WndProc;
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

void SMK_RegisterHotkeys(HWND hWnd)
{
	RegisterHotKey(hWnd, 0, 0, VK_MEDIA_PLAY_PAUSE);
	RegisterHotKey(hWnd, 1, 0, VK_MEDIA_NEXT_TRACK);
	RegisterHotKey(hWnd, 2, 0, VK_MEDIA_PREV_TRACK);
}

void SMK_UnregisterHotkeys(HWND hWnd)
{
	UnregisterHotKey(hWnd, 0);
	UnregisterHotKey(hWnd, 1);
	UnregisterHotKey(hWnd, 2);
}