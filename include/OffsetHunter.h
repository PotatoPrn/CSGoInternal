#ifndef CSGOINTERNAL_OFFSETHUNTER_H
#define CSGOINTERNAL_OFFSETHUNTER_H

#include "main.h"
#include <Windows.h>


struct OffsetValues
{
	uintptr_t m_iHealth;
	uintptr_t m_iTeamNum;
	uintptr_t m_vecOrigin;
	uintptr_t m_vecVelocity;
	uintptr_t m_vecViewOffset;

	uintptr_t* m_Forcejump;

};

extern OffsetValues OffsetV;

void LocateOffsets();



#endif //CSGOINTERNAL_OFFSETHUNTER_H