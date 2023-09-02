#include "main.h"


GameHack HackClass;
EnabledHacks THacks;

// DLL Init Routine
void InitHack(HMODULE hModule)
{

	// Setup Output Console
	AllocConsole();
	FILE* fHandle;
	freopen_s(&fHandle, "CONOUT$", "w", stdout);

	// Setup Class Variables

	HackClass.ClientName = "client.dll";
	HackClass.ClientBase = (uintptr_t)GetModuleHandle(HackClass.ClientName);

	HackClass.EngineName = "engine.dll";
	HackClass.EngineBase = (uintptr_t)GetModuleHandle(HackClass.EngineName);


	// Setup Player Entity
	HackClass.PlayerEntity = *(PlayerObject**)(HackClass.ClientBase + PresetOffset::dwLocalPlayer);

	// Setup Console
	UI::ClearConsole();
	UI::SetupConsole();

	// Setup Graphics Hooking Class...

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
	while (true)
	{
		// Setup Detach Hotkey
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			break;
		}

		if (GetAsyncKeyState(VK_F9) & 1)
		{
			THacks.T_BHop = !THacks.T_BHop;
		}

		if (GetAsyncKeyState(VK_SPACE) && THacks.T_BHop)
		{
			BHop_Hack();
		}

		std::cout << "[F9] Bhop Hack > " << THacks.T_BHop << std::endl;

		Sleep(10);

		UI::ClearConsole();
	}
	// Return and Kill Console
	return;
}