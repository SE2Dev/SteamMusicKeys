#pragma once
#include <Windows.h>

HWND SMK_CreateDummyWindow(HINSTANCE hInstance, LPWSTR title);
void SMK_MessageLoop(void);

void SMK_RegisterHotkeys(HWND hWnd);
void SMK_UnregisterHotkeys(HWND hWnd);