#include "main.h"

// DLL Init Routine
void InitHack(HMODULE hModule)
{

	// Setup Output Console
	AllocConsole();
	FILE* fHandle;
	freopen_s(&fHandle, "CONOUT$", "w", stdout);

	// Setup Class Variables
	GameHack HackClass;
	HackClass.ModuleName = "";
	HackClass.ModuleBase = (uintptr_t)GetModuleHandleA(HackClass.ModuleName);

	// Setup Console
	UI::ClearConsole();
	UI::SetupConsole();

	// Setup Graphics Hooking Class...
	HookInfo MainHook;

	// Call HackThread
	HackThread(HackClass);

	// Eject DLL
	fclose(fHandle);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}


// Start DLL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)InitHack, hModule, 0, nullptr));
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


// Main HackThread
void HackThread(GameHack HackClass)
{
	// Enter PlayerObject Offset Here
	HackClass.PlayerObject = *(PlayerEntity**)(HackClass.ModuleBase + 0);

	if (HackClass.PlayerObject)
	{
		while (true)
		{
			// Setup Detach Hotkey
			if (GetAsyncKeyState(VK_DELETE) & 1)
			{
				break;
			}
			Sleep(1);
		}
		// Return and Kill Console
		return;
	}
}