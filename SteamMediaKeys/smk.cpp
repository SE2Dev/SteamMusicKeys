#include "smk.h"

void SMK_TogglePlayback()
{
	if (IMus->GetPlaybackStatus() == AudioPlayback_Playing)
		IMus->Pause();
	else
		IMus->Play();
}

LRESULT WINAPI SMK_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_HOTKEY)
	{
		//
		// Prevent hotkeys from attempting to begin playback if queue is empty
		// as well as when steam music has not yet manually been initialized (AudioPlayback_Idle)
		// to prevent issues when using other media players
		//
		if (IMus->GetPlaybackStatus() != AudioPlayback_Idle)
		{
			switch (HIWORD(lParam))
			{
			case VK_MEDIA_PLAY_PAUSE:
				SMK_TogglePlayback();
				break;
			case VK_MEDIA_NEXT_TRACK:
				IMus->PlayNext();
				break;
			case VK_MEDIA_PREV_TRACK:
				IMus->PlayPrevious();
				break;
			}
		}
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