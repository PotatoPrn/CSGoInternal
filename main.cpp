#include "main.h"


// Declared Structs
GameHack HackClass;
EnabledHacks THacks;
ClrRenderStruct EnemyTeamColor;
ClrRenderStruct AllyTeamColor;
OffsetValues OffsetV;
LPDIRECT3DDEVICE9 pDevice = nullptr;



// Global Data
void* D3D9Device[119]; // Direct X Dummy Vtable
BYTE EndSceneBytes[7] { 0 }; // Byte storage to store the original bytes
tEndScene oEndScene = nullptr;



// Hook Function
void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{
	if (!pDevice)
	{
		pDevice = o_pDevice;
	}

	HackThread();

	// Not loading >_>

	oEndScene(pDevice); // Not Drawing?
}


// DLL Init Routine
void InitHack(HMODULE hModule)
{

	// Setup Output Console

	AllocConsole();
	FILE* fHandle;
	freopen_s(&fHandle, "CONOUT$", "w", stdout);


	// Setup Graphics Hooking Class...
	if (InitD3D9(D3D9Device, sizeof(D3D9Device)))
	{
		memcpy(EndSceneBytes, (char*)D3D9Device[42], 7);

		SetupThread();

		oEndScene = (tEndScene)Hook::TrampHook((char*)D3D9Device[42],(char*)hkEndScene,   7);
	}


	// Patch Original Bytes when quitting
	while (!GetAsyncKeyState(VK_DELETE))
	{
		Sleep(1);
	}

	Hook::Patch((BYTE*)D3D9Device[42], EndSceneBytes, 7);

	// Call HackThread
	//HackThread();


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

	// Setup Player Object Entity;
	HackClass.PlayerEntity = *(PlayerObject**)(HackClass.ClientBase + PresetOffset::dwLocalPlayer);
}