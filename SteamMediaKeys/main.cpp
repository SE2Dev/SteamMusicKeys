#include <Windows.h>

#include "smk.h"

#define STEAMAPI_STEAMISRUNNING_RETRY_COUNT 64
#define STEAMAPI_STEAMISRUNNING_RETRY_DELAY 1000

ISteamMusic* IMus = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	bool SteamAPI_SteamIsRunning = SteamAPI_IsSteamRunning();

	for(int i = 0; !SteamAPI_SteamIsRunning && i < STEAMAPI_STEAMISRUNNING_RETRY_COUNT; i++)
	{
		SteamAPI_SteamIsRunning = SteamAPI_IsSteamRunning();
		Sleep(STEAMAPI_STEAMISRUNNING_RETRY_DELAY);
	}

	if(!SteamAPI_SteamIsRunning)
	{
		MessageBox(0,L"ERROR: Could not initialize SteamAPI (Steam is not running)", 0, 0);
		return 1;
	}

	if(!SteamAPI_Init())
	{
		MessageBox(0, L"ERROR: Could not initialize SteamAPI", 0, 0);
		return 2;
	}

	if(!(IMus = SteamMusic()))
	{
		MessageBox(0, L"ERROR: Could not initialize Steam Music", 0, 0);
		SteamAPI_Shutdown();
		return 3;
	}

	HWND hWnd = SMK_CreateDummyWindow(hInstance, L"SteamMusicKeys");
	if(!hWnd)
	{
		MessageBox(0, L"ERROR: Could not create dummy window", 0, 0);
		SteamAPI_Shutdown();
		return 4;
	}

	SMK_RegisterHotkeys(hWnd);
	SMK_MessageLoop();

	SMK_UnregisterHotkeys(hWnd);
	SteamAPI_Shutdown();
	return 0;
}