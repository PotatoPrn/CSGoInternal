#ifndef INTTEMPLATE_MAIN_H
#define INTTEMPLATE_MAIN_H

// Standard C++ Headers
#include <iostream>
#include <vector>

// Windows Headers
#include <Windows.h>

// Offsets
#include "Offsets.h"

// Local Headers
#include "MemUtils.h"
#include "UiUtils.h"
#include "HookUtil.h"
#include "HackList.h"


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

};

extern EnabledHacks THacks;

void InitHack(HMODULE hModule);

void HackThread(GameHack HackClass);


#endif //INTTEMPLATE_MAIN_H
