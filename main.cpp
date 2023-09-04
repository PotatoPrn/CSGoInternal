#include "main.h"


// Declared Structs
GameHack HackClass;
EnabledHacks THacks;
ClrRenderStruct EnemyTeamColor;
ClrRenderStruct AllyTeamColor;
OffsetValues OffsetV;

// Key State Definitions
#define KEYDOWN -32768
#define KEYUP 0

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

	LocateOffsets();


	// Setup Player Entity
	do
	{
		HackClass.PlayerEntity = *(PlayerObject**)(HackClass.ClientBase + PresetOffset::dwLocalPlayer);
	} while (HackClass.PlayerEntity == NULL);

	// Setup Console
	UI::ClearConsole();
	UI::SetupConsole();

	// Setup Graphics Hooking Class...


	// Call HackThread
	HackThread();


	// Eject DLL
	// May need a cleanup thread here...
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
void HackThread()
{
	while (true)
	{

		/// DLL Detach Hotkey
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			break;
		}


		/// Aimbot Hack Toggle
		if (GetAsyncKeyState(VK_F7) & 1)
		{
			THacks.T_AimBot = !THacks.T_AimBot;
		}

		/// Glow Hack Toggle
		if (GetAsyncKeyState(VK_F8) & 1)
		{
			GlowUtils::ModifyBrightness();
			THacks.T_Glow = !THacks.T_Glow;
		}

		/// BHop Related Hack Toggle
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			THacks.T_BHop = !THacks.T_BHop;
		}


		/// Triggerbot Hack Toggle
		if (GetAsyncKeyState(VK_F10) & 1)
		{
			THacks.T_TrigBot = !THacks.T_TrigBot;
		}

		if (GetAsyncKeyState(VK_SHIFT) == KEYDOWN && !THacks.T_TrigBot2)
		{
			THacks.T_TrigBot = true;
			THacks.T_TrigBot2 = true;
		}

		if (GetAsyncKeyState(VK_SHIFT) == KEYUP && THacks.T_TrigBot2)
		{
			THacks.T_TrigBot = false;
			THacks.T_TrigBot2 = false;
		}








		/// Hack Execution Loop
		if (THacks.T_TrigBot)
		{
			TriggerBot();
		}


		if (GetAsyncKeyState(VK_SPACE) && THacks.T_BHop)
		{
			BHop_Hack();
		}

		if (THacks.T_Glow)
		{
			Glow_Hack();
		}




		// Toggled Hacks Cout
		std::cout << "[F7] Aimbot Hack > " << THacks.T_AimBot << std::endl;
		std::cout << "[F8] Glow Hack > " << THacks.T_Glow << std::endl;
		std::cout << "[F9] Bhop Hack > " << THacks.T_BHop << std::endl;
		std::cout << "[F10] / [Shift] Triggerbot Hack > " << THacks.T_TrigBot << std::endl;

		Sleep(10);

		UI::ClearConsole();
	}
	// Return and Kill Console
	return;
}