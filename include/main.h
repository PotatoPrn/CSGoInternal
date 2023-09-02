#ifndef INTTEMPLATE_MAIN_H
#define INTTEMPLATE_MAIN_H

// Standard C++ Headers
#include <iostream>
#include <vector>

// Windows Headers
#include <Windows.h>


// Local Headers
#include "MemUtils.h"
#include "UiUtils.h"
#include "HookUtil.h"

// Offsets
#include "Offsets.h"

struct GameHack
{
public:
	const char* ModuleName;
	uintptr_t ModuleBase;
	PlayerEntity* PlayerObject;
};

// Enabled Hacks Class, Ensure They are at false...
struct EnabledHacks
{
public:


};

void InitHack(HMODULE hModule);

void HackThread(GameHack HackClass);


#endif //INTTEMPLATE_MAIN_H
