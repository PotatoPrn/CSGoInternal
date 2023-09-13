#ifndef CSGOINTERNAL_OFFSETHUNTER_CPP
#define CSGOINTERNAL_OFFSETHUNTER_CPP

#include "Sdk/OffsetHunter.h"
#include "Sdk/SDKFunctions.h"

#include "Utils/MemUtils.h"

#include <iostream>

/*
 * /// Offset Hunting Example
		IClientEntityList* ClientEntList = (IClientEntityList*)GetInterface("client.dll", "VClientEntityList003");

		uintptr_t ent2 = (uintptr_t)ClientEntList->GetClientEntity(2);

		IBaseClientDLL* BaseClassDLL = (IBaseClientDLL*)GetInterface("client.dll", "VClient018");

		ClientClass* clientclass = BaseClassDLL->GetAllClasses();

		uintptr_t HealthOffset = GetNetVarOffset("DT_BasePlayer", "m_iHealth", clientclass);

		int* Health = (int*)(ent2 + HealthOffset);

		std::cout << "Ent2 Health > " << *Health << std::endl;
		*/

bool LocateOffsets()
{
	IBaseClientDLL* BaseClassDLL = (IBaseClientDLL*)GetInterface("client.dll", "VClient018");

	ClientClass* clientclass = BaseClassDLL->GetAllClasses();

	// NetVars
	OffsetV.m_iHealth = GetNetVarOffset("DT_BasePlayer", "m_iHealth", clientclass ,0); // 0x100
	OffsetV.m_iTeamNum = GetNetVarOffset("DT_BasePlayer", "m_iTeamNum", clientclass ,0); // 0xF4
	OffsetV.m_vecOrigin = GetNetVarOffset("DT_BasePlayer", "m_vecOrigin", clientclass ,0); // 0x138

	OffsetV.m_dwBoneMatrix = GetNetVarOffset("DT_BaseAnimating", "m_nForceBone", clientclass ,28);

	OffsetV.m_fFlag = GetNetVarOffset("DT_CSPlayer", "m_fFlags", clientclass ,0);
	OffsetV.m_bIsDefusing = GetNetVarOffset("DT_CSPlayer", "m_bIsDefusing", clientclass ,0);
	OffsetV.m_vecVelocity = GetNetVarOffset("DT_CSPlayer", "m_vecVelocity[0]", clientclass ,0); // 0x114
	OffsetV.m_vecViewOffset = GetNetVarOffset("DT_CSPlayer", "m_vecViewOffset[0]", clientclass ,0); // 0x108
	OffsetV.m_iCrosshairId = GetNetVarOffset("DT_CSPlayer", "m_bHasDefuser", clientclass, 92); //
	OffsetV.m_iGlowIndex = GetNetVarOffset("DT_CSPlayer", "m_flFlashDuration", clientclass, 24);

	OffsetV.m_clrRender = GetNetVarOffset("DT_BaseEntity", "m_clrRender", clientclass,0);




	// DLL Pointers

	/* Example of Pointer Dereference
	 * An example but a shitposty crap example lmap
	 * uintptr_t ForceJumpPtr = (uintptr_t)Mem::InternalScanModule("client.dll", "\x8B\x0D\xFF\xFF\xFF\xFF\x8B\xD6\x8B\xC1\x83\xCA\x02", "xx????xxxxxxx") + 0x02;
	 * uintptr_t* Test = (uintptr_t*)ForceJumpPtr; // Cast the address as a address pointer
	 * std::cout << (uintptr_t*)*Test << std::endl; // Retrieve the Dereferenced value
	 * https://www.unknowncheats.me/forum/counterstrike-global-offensive/247851-internal-pattern-scanning.html
	 */

	/// Non Offset Address
	OffsetV.dwForceJump = Mem::InternalScanModule("client.dll", "\x8B\x0D\xFF\xFF\xFF\xFF\x8B\xD6\x8B\xC1\x83\xCA\x02","xx????xxxxxxx", 0x02, 0x0);
	OffsetV.model_ambient_min = Mem::InternalScanModule("engine.dll", "\xF3\x0F\x10\x0D\xFF\xFF\xFF\xFF\xF3\x0F\x11\x4C\x24\xFF\x8B\x44\x24\x20\x35\xFF\xFF\xFF\xFF\x89\x44\x24\x0C", "xxxx????xxxxx?xxxxx????xxxx" ,0x04, 0x0);
	OffsetV.dwClientState = Mem::InternalScanModule("engine.dll", "\xA1\xFF\xFF\xFF\xFF\x6A\x00\x56\x8B\x88", "x????xxxxx", 0x01, 0x0);
	OffsetV.dwClientState_ViewAngles = (uintptr_t)Mem::InternalScanModule("engine.dll", "\xF3\x0F\x11\x86\xFF\xFF\xFF\xFF\xF3\x0F\x10\x44\x24\xFF\xF3\x0F\x11\x86", "xxxx????xxxxx?xxxx", 0x04, 0x0);
	OffsetV.dwGlowObjectManager = Mem::InternalScanModule("client.dll", "\xA1\xFF\xFF\xFF\xFF\xA8\x01\x75\x4B", "x????xxxx", 0x01, 0x01);

	/// Offsets
	OffsetV.m_bDormant = (uintptr_t)Mem::InternalScanModule("client.dll", "\x8B\xF1\x88\x9E\xFF\xFF\xFF\xFF\xE8", "xxxx????x", 0x04, 0x00);
	OffsetV.dwEntityList = (uintptr_t)Mem::InternalScanModule("client.dll", "\xBB\xFF\xFF\xFF\xFF\x83\xFF\x01\x0F\x8C\xFF\xFF\xFF\xFF\x3B\xF8", "x????xxxxx????xx", 0x01,0x0);

	return true;

}

#endif //CSGOINTERNAL_OFFSETHUNTER_CPP