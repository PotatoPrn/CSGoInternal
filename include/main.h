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
#include "Offsets.h"
#include "OffsetHunter.h"

// Local Headers
#include "MemUtils.h"
#include "UiUtils.h"
#include "HackList.h"
#include "HookUtil.h"
#include "DirectX.h"
#include "Draw.h"
#include "MainThread.h"


// Sdk Stuff


struct GameHack
{
public:
	const char* ClientName;
	const char* EngineName;
	uintptr_t ClientBase;
	uintptr_t EngineBase;
	PlayerObject* PlayerEntity;

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
};

extern EnabledHacks THacks;

void InitHack(HMODULE hModule);

void SetupThread();


#endif //INTTEMPLATE_MAIN_H
