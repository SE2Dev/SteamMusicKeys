#include <Windows.h>
#include "smk.h"

#define STEAMAPI_STEAMISRUNNING_RETRY_COUNT 64
#define STEAMAPI_STEAMISRUNNING_RETRY_DELAY 1000

ISteamMusic* IMus = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//
	// Console window is required for the program to automatically close when the user quits Steam
	//
	if(AllocConsole())
	{
		FILE* stream = nullptr;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONOUT$", "w", stderr);
		freopen_s(&stream, "CONIN$", "r", stdin);

		printf("SteamMusicKeys\n\n");
	}

	printf("Searching for Steam...	");
	bool SteamAPI_SteamIsRunning = SteamAPI_IsSteamRunning();

	for(int i = 0; i < STEAMAPI_STEAMISRUNNING_RETRY_COUNT; i++)
	{
		if(SteamAPI_SteamIsRunning = SteamAPI_IsSteamRunning())
		{
			printf("Found!\n");
			break;
		}
		Sleep(STEAMAPI_STEAMISRUNNING_RETRY_DELAY);
	}

	if(!SteamAPI_SteamIsRunning)
	{
		printf("Not Found!\n");
		MessageBox(0,L"ERROR: Could not initialize SteamAPI (Steam is not running)", 0, 0);
		FreeConsole();
		return 1;
	}

	printf("Initializing SteamAPI...\n");
	if(!SteamAPI_Init())
	{
		MessageBox(0, L"ERROR: Could not initialize SteamAPI", 0, 0);
		FreeConsole();
		return 2;
	}

	printf("Initializing Steam Music...\n");
	if(!(IMus = SteamMusic()))
	{
		MessageBox(0, L"ERROR: Could not initialize Steam Music", 0, 0);
		SteamAPI_Shutdown();
		FreeConsole();
		return 3;
	}

	printf("Creating dummy window...\n");
	HWND hWnd = SMK_CreateDummyWindow(hInstance, L"SteamMusicKeys");
	if(!hWnd)
	{
		MessageBox(0, L"ERROR: Could not create dummy window", 0, 0);
		SteamAPI_Shutdown();
		FreeConsole();
		return 4;
	}

	printf("Registering hotkeys...\n");
	SMK_RegisterHotkeys(hWnd);
	printf("Hiding console...\n");
	ShowWindow (GetConsoleWindow(), SW_HIDE);
	SMK_MessageLoop();

	printf("Showing console...\n");
	ShowWindow (GetConsoleWindow(), SW_SHOW);
	printf("Freeing Hotkeys...\n");
	SMK_UnregisterHotkeys(hWnd);
	printf("Freeing SteamAPI\n");
	SteamAPI_Shutdown();
	printf("Freeing Console\n");
	FreeConsole();
	return 0;
}