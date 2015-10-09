#include <Windows.h>

#pragma warning(push, 0)  
#include "sdk\public\steam\steam_api.h"
#pragma comment(lib, "sdk\\redistributable_bin\\steam_api.lib")
#pragma warning(pop)  

#include "smk.h"

#define STEAMAPI_STEAMISRUNNING_RETRY_COUNT 64
#define STEAMAPI_STEAMISRUNNING_RETRY_DELAY 1000

static ISteamMusic* IMus = nullptr;

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

	SMK_MessageLoop();

	SteamAPI_Shutdown();
	return 0;
}