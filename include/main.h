#ifndef INTTEMPLATE_MAIN_H
#define INTTEMPLATE_MAIN_H

// Standard C++ Headers
#include <iostream>
#include <vector>

// Graphics Library
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern LPDIRECT3DDEVICE9 pDevice;

// Windows Headers
#include <Windows.h>

// Offsets
#include "Sdk/VecStruct.h"
#include "Sdk/OffsetHunter.h"

// Local Headers
#include "Utils/MemUtils.h"
#include "Utils/UiUtils.h"
#include "HackList.h"
#include "Utils/HookUtil.h"
#include "DX9Utils/DirectX.h"
#include "DX9Utils/Draw.h"
#include "MainThread.h"
#include "TraceRayUtil.h"
#include "Utils/HelperUtils.h"


// Sdk Stuff


struct GameHack
{
public:
	const char* ClientName;
	const char* EngineName;
	uintptr_t ClientBase;
	uintptr_t EngineBase;
	uintptr_t PlayerEntity;

};

extern GameHack HackClass;

// Enabled Hacks Class, Ensure They are at false...
struct EnabledHacks
{
public:
	bool T_BHop = false;
	bool T_Glow = false;
	bool T_TrigBot = false;
	bool T_TrigBot2 = false;
	bool T_AimBot = false;
	bool T_ESP = false;
	bool T_RCS = false;

	void KillAll()
	{
		T_BHop = T_Glow = T_TrigBot = T_TrigBot2 = T_AimBot = T_ESP = T_RCS = 0;
	}
};

extern EnabledHacks THacks;

void InitHack(HMODULE hModule);

void SetupThread();


#endif //INTTEMPLATE_MAIN_H
