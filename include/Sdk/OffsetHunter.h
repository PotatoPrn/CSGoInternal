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

	uintptr_t* m_Forcejump;

};

extern OffsetValues OffsetV;

bool LocateOffsets();


#endif //CSGOINTERNAL_OFFSETHUNTER_H