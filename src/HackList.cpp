#ifndef CSGOINTERNAL_HACKLIST_CPP
#define CSGOINTERNAL_HACKLIST_CPP

#include "HackList.h"


void BHop_Hack()
{
	if (FPSUtils::IsPlayerMoving())
	{
		int JumpState = HackClass.PlayerEntity->m_fFlag;

		static int FL_ONGROUND = 0b0000'0001; // Bitwise pattern for the player being on ground

		if (JumpState & FL_ONGROUND)
		{
			*(uintptr_t*)(HackClass.ClientBase + PresetOffset::dwForceJump) = 6;
		}
	}

}


#endif //CSGOINTERNAL_HACKLIST_CPP