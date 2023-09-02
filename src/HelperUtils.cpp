#ifndef CSGOINTERNAL_HELPERUTILS_CPP
#define CSGOINTERNAL_HELPERUTILS_CPP

#include "HelperUtils.h"

bool FPSUtils::IsPlayerMoving()
{
	Vec3 PlayerAcceleration = HackClass.PlayerEntity->m_vecvelocity;
	int TotalAcceleration = PlayerAcceleration.X + PlayerAcceleration.Y + PlayerAcceleration.Z;

	if (TotalAcceleration != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


#endif //CSGOINTERNAL_HELPERUTILS_CPP