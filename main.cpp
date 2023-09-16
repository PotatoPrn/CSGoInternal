#include "main.h"


// Declared Structs
GameHack HackClass;
EnabledHacks THacks;
ClrRenderStruct EnemyTeamColor;
ClrRenderStruct AllyTeamColor;
OffsetValues OffsetV;
LPDIRECT3DDEVICE9 pDevice = nullptr;
tTraceRay TraceRay;


// Global Data
void* D3D9Device[119]; // Direct X Dummy Device Vtable Storage
BYTE EndSceneBytes[7] { 0 }; // Byte storage to store the original bytes so i can repatch it with the original bytes to exit
tEndScene oEndScene = nullptr;



// Hook Function
void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
	if (!pDevice)
	{
		pDevice = o_pDevice;
	}

	HackThread();

	oEndScene(pDevice);
}


// DLL Init Routine
void InitHack(HMODULE hModule)
{

	// Setup Output Console

	AllocConsole();
	FILE* fHandle;
	freopen_s(&fHandle, "CONOUT$", "w", stdout);


	// Setup Graphics Hooking function...
	if (InitD3D9(D3D9Device, sizeof(D3D9Device)))
	{
		// Copy original bytes into storage buffer
		memcpy(EndSceneBytes, (char*)D3D9Device[42], 7);

		// Execute Setup Thread ie Offset Locating
		SetupThread();

		// Hook the main hack function
		oEndScene = (tEndScene)Hook::TrampHook((char*)D3D9Device[42],(char*)hkEndScene,   7);
	}



	while (!GetAsyncKeyState(VK_DELETE))
	{
		Sleep(1);
	}

	// The entire dll will crash if all functions are still enabled...
	// Adding a temporary functon clean up
	THacks.KillAll();


	// Patch Original Bytes when so the dll can eject without the game crashing
	Sleep(10);
	Hook::Patch((BYTE*)D3D9Device[42], EndSceneBytes, 7);

	std::cout << "Ejecting" << std::endl;

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


void SetupThread()
{
	do
	{
		HackClass.ClientName = "client.dll";
		HackClass.ClientBase = (uintptr_t)GetModuleHandle(HackClass.ClientName);
	} while (HackClass.ClientBase == NULL);


	do
	{
		HackClass.EngineName = "engine.dll";
		HackClass.EngineBase = (uintptr_t)GetModuleHandle(HackClass.EngineName);
	} while (HackClass.EngineBase == NULL);

	LocateOffsets();

	// Setup Console
	UI::ClearConsole();
	UI::SetupConsole();
}