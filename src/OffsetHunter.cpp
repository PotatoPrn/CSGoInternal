#ifndef CSGOINTERNAL_OFFSETHUNTER_CPP
#define CSGOINTERNAL_OFFSETHUNTER_CPP

#include "OffsetHunter.h"
#include "SDKFunctions.h"
#include "MemUtils.h"

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
	OffsetV.m_iHealth = GetNetVarOffset("DT_BasePlayer", "m_iHealth", clientclass);
	OffsetV.m_iTeamNum = GetNetVarOffset("DT_BasePlayer", "m_iTeamNum", clientclass);
	OffsetV.m_vecOrigin = GetNetVarOffset("DT_BasePlayer", "m_vecOrigin", clientclass);
	OffsetV.m_vecVelocity = GetNetVarOffset("DT_CSPlayer", "m_vecVelocity", clientclass);
	OffsetV.m_vecViewOffset = GetNetVarOffset("DT_CSPlayerr", "m_vecViewOffset", clientclass);


	// DLL Pointers

	/* Example of Pointer Dereference
	 * uintptr_t ForceJumpPtr = (uintptr_t)Mem::InternalScanModule("client.dll", "\x8B\x0D\xFF\xFF\xFF\xFF\x8B\xD6\x8B\xC1\x83\xCA\x02", "xx????xxxxxxx") + 0x02;
	 * uintptr_t* Test = (uintptr_t*)ForceJumpPtr; // Cast the address as a address pointer
	 * std::cout << (uintptr_t*)*Test << std::endl; // Retrieve the Dereferenced value
	 * https://www.unknowncheats.me/forum/counterstrike-global-offensive/247851-internal-pattern-scanning.html
	 */

	uintptr_t ForceJumpPtr = (uintptr_t)Mem::InternalScanModule("client.dll", "\x8B\x0D\xFF\xFF\xFF\xFF\x8B\xD6\x8B\xC1\x83\xCA\x02", "xx????xxxxxxx") + 0x02;
	OffsetV.m_Forcejump = (uintptr_t*)*((uintptr_t*)ForceJumpPtr);

	return true;

}

#endif //CSGOINTERNAL_OFFSETHUNTER_CPP