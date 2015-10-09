#pragma once
#include <Windows.h>

#pragma warning(push, 0)  
#include "sdk\public\steam\steam_api.h"
#pragma comment(lib, "sdk\\redistributable_bin\\steam_api.lib")
#pragma warning(pop) 

extern ISteamMusic* IMus;

HWND SMK_CreateDummyWindow(HINSTANCE hInstance, LPWSTR title);
void SMK_MessageLoop(void);

void SMK_RegisterHotkeys(HWND hWnd);
void SMK_UnregisterHotkeys(HWND hWnd);