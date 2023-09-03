#ifndef CSGOINTERNAL_OFFSETHUNTER_CPP
#define CSGOINTERNAL_OFFSETHUNTER_CPP

#include "OffsetHunter.h"
#include "SDKFunctions.h"

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

void LocateOffsets()
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


}

#endif //CSGOINTERNAL_OFFSETHUNTER_CPP