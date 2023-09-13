#ifndef CSGOINTERNAL_OFFSETHUNTER_H
#define CSGOINTERNAL_OFFSETHUNTER_H

#include <Windows.h>


// turn it in a class...
struct OffsetValues
{
	uintptr_t m_iHealth;
	uintptr_t m_iTeamNum;
	uintptr_t m_vecOrigin;
	uintptr_t m_vecVelocity;
	uintptr_t m_vecViewOffset;
	uintptr_t m_iCrosshairId;
	uintptr_t m_iGlowIndex;
	uintptr_t m_clrRender;
	uintptr_t m_fFlag;
	uintptr_t m_dwBoneMatrix;
	uintptr_t m_bIsDefusing;


	uintptr_t dwForceJump;
	uintptr_t model_ambient_min;
	uintptr_t dwClientState;
	uintptr_t dwClientState_ViewAngles;
	uintptr_t dwGlowObjectManager;
	uintptr_t dwLocalPlayer;
	uintptr_t dwForceAttack;

	uintptr_t m_bDormant;
	uintptr_t dwEntityList;
};




extern OffsetValues OffsetV;

bool LocateOffsets();
#endif //CSGOINTERNAL_OFFSETHUNTER_H